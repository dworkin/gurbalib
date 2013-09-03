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
#define DEFAULT_SEARCHPATH ({ "/cmds/player/" })

string *searchpath;

static void create() {
   searchpath = ({});
}

private void DBT(string str) {
   mixed flag;
   if(this_player()) {
      flag = this_player()->query_env("debug_commands");
      if(stringp(flag) && (flag == "1" || flag == "on")) {
         flag = 1;
      } else if(!intp(flag)) {
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
   return COMMAND_D->cmd_path_exists( path );
}

/* add a trailing slash if its not there */
private string trailing_slash( string str ) {
   if (strlen(str) && str[strlen(str)-1] != '/') {
      str += "/";
   }
   return str;
}

/* set the searchpath, accepts either : delimited string or array
   Note that $PATH is replaced by the current search path         */
static void set_searchpath( mixed path ) {
   int i, sz;
   string *result;
   DBT("set_searchpath("+dump_value(path)+")\n");

   result = ({ });

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
         if(path[i][0] != '/') {
            error("Command path must start with a / ["+path[i]+"]");
         }
         path[i] = trailing_slash(path[i]);
         if( validate_cmd_path( path[i] ) ) {
            /* prevent duplicates */
            result |= ({ path[i] });
            DBT("Validate " + path[i] + ": OK\n");
         } else {
            DBT("Validate " + path[i] + ": not found.\n");
         }
      }
   }

   searchpath = result;
}

static string query_searchpath() {
   return searchpath ? implode( searchpath, ":" ) : nil;
}

static void set_cmd_path( string *path ) {
   set_searchpath(path);
}

static string *query_cmd_path() {
   if(searchpath && sizeof(searchpath)) {
      return searchpath[..];
   } else {
      return ({ });
   }
}

static void add_cmd_path( string path ) {
   set_searchpath( searchpath | ({ path }) );
}

static void remove_cmd_path( string path ) {
   set_searchpath( searchpath - ({ path }) );
}

static int command(string cmd, string arg, varargs string *path) {
   /* no direct call_outs to command() allowed for security reasons */
   if(CALLOUT()) {
      error("Direct call_outs to command() not allowed");
   }

   if(!path) path = searchpath;
   if(!path) path = DEFAULT_SEARCHPATH;
   return COMMAND_D->exec_command(cmd, arg, path );
}

