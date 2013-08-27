/*
 * Gurbalib interface for using commands
 *
 * Aidil @ Way of the Force.
 *
 * This code is in the public domain
 *
 */

#include <privileges.h>
#include <type.h>

#define DEBUG

string *searchpath;

static void create() {
   searchpath = ({});
}

private void DBT(string str) {
   mixed flag;
   if(this_player()) {
      flag = this_player()->get_env("debug_commands");
      if(flag == "1" || flag == "on") {
         flag = 1;
      } else {
         flag = 0;
      }
      if(flag) this_player()->out(str);
   }
#ifdef DEBUG
   console_msg(str);
#endif
}

/* does the command path exist? access checks are done on usage */
private int validate_cmd_path( string path ) {
   int r;
   r = COMMAND_D->cmd_path_exists( path );
   DBT("validate_cmd_path("+path+"), returning " + r + "\n");
   return r;
}

/* add a trailing slash if its not there */
private string trailing_slash( string str ) {
   if (strlen(str) && str[strlen(str)-1] != '/') {
      str += "/";
   }
   return str;
}

static void set_searchpath( mixed path ) {
   int i, sz;
   DBT("set_searchpath("+dump_value(path)+")\n");
   switch(typeof(path)) {
      case T_STRING : path = explode( path, ":" );
                      break;

      case T_ARRAY  : break;

      case T_NIL    : searchpath = nil;
                      return;

      default       : error("Bad argument 1 to set_searchpath (string or array of strings expected)");
   }
   /* note, need to recheck size of the array for each iteration */
   for( i = 0; i < sizeof( path ); i++ ) {
      if(!path[i]) {
         continue;
      } else if(!stringp(path[i])) {
         error("Bad element in argument 1 to set_searchpath (array of strings expected)");
      }
      if(path[i][0] == '$') {
         switch(path[i][1..]) {
            case "PATH" : DBT("replacing $PATH with " + dump_value( searchpath ) + "\n");
                          path = path[..i-1] + searchpath + path[i+1..];
                          i--; /* need to re-iterate over this one as we replaced it */
                          break;
            default     : error(path[i][1..] + " not recognized.");
                          break;
         }
      } else {
         string tmpname;
         path[i] = trailing_slash(path[i]);
         tmpname = path[i];
         /* nil this element, we'll remove it later */
         path[i] = validate_cmd_path( path[i] ) ? path[i] : nil;
         DBT("validated " + tmpname + ": " + (path[i] ? "ok" : "not found") + "\n");
      }
   }

   /* remove 'removed' paths from the array */
   path -= ({ nil });
   searchpath = path;
}

static string query_searchpath() {
   return searchpath ? implode( searchpath, ":" ) : nil;
}

static void set_cmd_path( string *path ) {
   set_searchpath(path);
}

static string *query_cmd_path() {
   searchpath ? searchpath[..] : ({ });
}

static void add_cmd_path( string path ) {
   set_searchpath( searchpath | ({ path }) );
}

static void remove_cmd_path( string path ) {
   set_searchpath( searchpath - ({ path }) );
}

static int command(string cmd, string arg) {
   /* no direct call_outs to command() allowed for security reasons */
   if(CALLOUT()) {
      error("Direct call_outs to command() not allowed");
   }

   return COMMAND_D->exec_command(cmd, arg, searchpath );
}

