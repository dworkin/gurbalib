/*
 * Gurbalib interface for using commands
 *
 * Aidil @ Way of the Force.
 *
 * This code is in the public domain
 *
 */

inherit "/std/modules/m_messages";

/* Uncomment this to debug */
/* #define DEBUG_M_CMD 1 */

#include <privileges.h>
#include <type.h>
#define DEFAULT_SEARCHPATH ({ "/cmds/player/" })

string *searchpath;

/* Commands that are local to worn/wielded items */
static mapping item_commands;

static void create(void) {
   searchpath = ({});
}

private void DBT(string str) {
   if (this_player()) {
      if (this_player()->query_debug_commands() ) {
         this_player()->out(str);
      }
   }
#ifdef DEBUG_M_CMD
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

   DBT("set_searchpath(" + dump_value(path) + ")\n");

   result = ({ });

   switch (typeof(path)) {
      case T_STRING: 
         path = explode( path, ":" );
         break;
      case T_ARRAY: 
         break;
      case T_NIL: 
         searchpath = nil;
         return;

      default: 
         error("Bad argument 1 to set_searchpath (string or array of " +
            "strings expected)");
   }

   /* note, need to recheck size of the array for each iteration */
   for ( i = 0; i < sizeof( path ); i++ ) {
      if (!path[i]) {
         continue;
      } else if (!stringp(path[i])) {
         error("Bad element in argument 1 to set_searchpath (array of " +
            "strings expected)");
      }
      if (path[i][0] == '$') {
         switch (path[i][1..]) {
            case "PATH":
               DBT("replacing $PATH with " + dump_value( searchpath ) + "\n");
               path = path[..i - 1] + searchpath + path[i + 1..];
               i--; /* need to re-iterate over this one as we replaced it */
               break;
            default:
               error(path[i][1..] + " not recognized.");
               break;
         }
      } else {
         if (path[i][0] != '/') {
            error("Command path must start with a / [" + path[i] + "]");
         }
         path[i] = trailing_slash(path[i]);
         if (validate_cmd_path(path[i])) {
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

static string query_searchpath(void) {
   if (searchpath) {
      return implode( searchpath, ":" );
   }

   return nil;
}

static void set_cmd_path( string *path ) {
   set_searchpath(path);
}

static string *query_cmd_path(void) {
   if (searchpath && sizeof(searchpath)) {
      return searchpath[..];
   } else {
      return ({ });
   }
}

static void add_cmd_path( string path ) {
   set_searchpath( searchpath | ({ path }) );
}

static void remove_cmd_path( string path ) {
/* XXX This doesn't seem to be working right. */
   set_searchpath( searchpath - ({ path }) );
}

static int command(string cmd, string arg, varargs string *path) {
   /* no direct call_outs to command() allowed for security reasons */
   if (CALLOUT()) {
      error("Direct call_outs to command() not allowed");
   }

   if (!path) {
      path = searchpath;
   }
   if (!path) {
      path = DEFAULT_SEARCHPATH;
   }
   return COMMAND_D->exec_command(cmd, arg, path );
}

/* Add to the item command mapping */
void add_item_command(string command, object ob) {
   if (!item_commands) {
      item_commands = ([]);
   }
   item_commands[command] = ob;
}

void remove_item_command(string command) {
   if (!item_commands) {
      item_commands = ([]);
   }
   item_commands[command] = nil;
}

/* Check for an item command */
int check_item_command(string cmd, string arg) {
   int i, sz;
   string *item_cmds;

   if (!item_commands) {
      item_commands = ([]);
   }

   item_cmds = map_indices(item_commands);
   sz = sizeof(item_cmds);
   for (i = 0; i < sz; i++) {
      if (item_cmds[i] == cmd) {
         /* Should we return the call_other not 1? XXX */
         call_other(item_commands[item_cmds[i]], "do_" + cmd, arg);
         return 1;
      }
   }
   return 0;
}

int check_emote(string cmd, string arg) {
   string rule, *rules;
   object target;

   if (EMOTE_D->is_emote(cmd) || cmd == "random") {

      if (cmd == "random") {
         cmd = EMOTE_D->get_random_emote();
      }

      rules = EMOTE_D->query_rules(cmd);

      if (arg != "") {
         target = this_environment()->present(arg);
      } else {
         target = nil;
      }

      if (target) {
         /* We've found our target, check for the correct rule */
         if (target->is_living()) {
            /* We're looking for a LIV rule */
            if (member_array("LIV", rules) != -1) {
               rule = "LIV";
            } else {
               rule = "";
            }
         } else {
            /* We're looking for a OBJ rule */
            if (member_array("OBJ", rules) != -1) {
               rule = "OBJ";
            } else {
               rule = "";
            }
         }
      } else {
         /* Or are we just looking for a string? */
         if ((member_array("STR", rules) != -1) && (arg != "")) {
            rule = "STR";
         } else {
            rule = "";
         }
      }

      if (rule == "LIV") {
         targeted_action(EMOTE_D->query_emote(cmd, rule), target);
      } else if (rule == "OBJ") {
         simple_action(EMOTE_D->query_emote(cmd, rule), target);
      } else if (rule == "STR") {
         simple_action(EMOTE_D->query_emote(cmd, rule), arg);
      } else if (member_array("", rules) != -1) {
         simple_action(EMOTE_D->query_emote(cmd, rule));
      } else {
         write("No such emote.\n");
      }
      return 1;
   }
   return 0;
}

int do_game_command(string message) {
   string cmd, arg, *path;
   int flag;
   object save_player;

   arg = "";

   save_player = this_player();
   set_this_player(this_object());

   catch {
      if (sscanf(message, "%s %s", cmd, arg) != 2) {
         cmd = message;
      }

      if (arg == "me") {
         arg = this_player()->query_id();
      }

      flag = 0;

      if (!this_player()->is_player()) {
         path = ({ "/cmds/monster/", "/cmds/player/" });
      } else {
         path = this_player()->query_path();
      }

      if (command(cmd, arg, path) != -1) {
         flag = 1;
      }

      if (!flag) {
         flag = check_item_command(cmd, arg);
      }

      /* check for emotes */
      if (!flag) {
         flag = check_emote(cmd, arg);
      }

   } : {
      set_this_player(save_player);
      rethrow();
   }

   set_this_player(save_player);
   return flag;
}
