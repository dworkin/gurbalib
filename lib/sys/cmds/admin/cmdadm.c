/*
 * Menu interface and CLI for managing the command system.
 * Also a small demo of the menu system itself.
 * August 2013, Aidil@Way of the Force
 * This code is in the public domain.
 */

inherit M_COMMAND;
inherit "/sys/lib/menu";

static int menu_cmdadm(varargs mixed junk...);

string *query_usage() {
   string *lines;
   lines = ({ "Usage: cmdadm <cmd> [path] [priv]" });
   lines += ({ "where cmd is one of add, remove, delete, privilege, show," });
   lines += ({ "list or menu." });
   lines += ({ " " });
   lines += ({ "%^BOLD%^add <path> <privilege>%^RESET%^" });
   lines += ({ " " });
   lines += ({ "  Add a new command path with a privilege to the command " +
      "daemon." });
   lines += ({ " " });
   lines += ({ "%^BOLD%^remove <path>" });
   lines += ({ "delete <path>%^RESET%^" });
   lines += ({ " " });
   lines += ({ "  Remove an existing command path from the command daemon." });
   lines += ({ "  This does NOT remove the files in that path, it merely " +
      "stops" });
   lines += ({ "  the commands defined in those files from being used as " +
      "commands." });
   lines += ({ " " });
   lines += ({ "%^BOLD%^privilege <path> <priv>%^RESET%^" });
   lines += ({ " " });
   lines += ({ "  Change the privilege required for using <path>." });
   lines += ({ " " });
   lines += ({ "%^BOLD%^list" });
   lines += ({ "show%^RESET%^" });
   lines += ({ " " });
   lines += ({ "  List command paths known to the command daemon." });
   lines += ({ " " });
   lines += ({ "%^BOLD%^menu%^RESET%^" });
   lines += ({ " " });
   lines += ({ "  Starts the menu driven interface, default action when no" });
   lines += ({ "  command is specified." });
   lines += ({ " " });
   lines += ({ "All commands can be abbreviated to their first 2 letters" });
   lines += ({ "so \"remove\" becomes \"re\", \"privilege\" becomes \"pr\"" });
   lines += ({ "(this does not work for \"menu\", as \"me\" has a special " +
      "meaning" });
   lines += ({ "but using \"men\" will work)"});
   lines += ({ " " });
   lines += ({ "Privilege can be any valid privilege or * for everyone" });
   lines += ({ " " });
   lines += ({ "Whenever a command expects more then one argument, where one" });
   lines += ({ "is a path, and the path contains spaces, you will need to " +
      "quote" });
   lines += ({ "the path, for example: cmdadm add \"/a path/with spaces/\" *" 
      });

   return lines;
}

void usage() {
   this_player()->more(map_array(query_usage(), "parse_colors", ANSI_D));
}

/* utility function, ensure every command path has a trailing slash.  */
private string trailing_slash( string str ) {
   if(str && strlen(str) && str[strlen(str)-1] != '/') {
      str += "/";
   }
   return str;
}

/*
 * utility function, pad string
 *
 */

private string padstr(string str, int len) {
   string r;

   argcheck(str != nil, 1, "string");
   r = str + "                                                                                                                                                      ";
   argcheck((len >= 0 && len < strlen(r)), 2, "ranged int [" + 0 + ".." + (strlen(r)-1) + "], got " + len);
   return r[..len-1];
}

/*
 *
 * The menu interface.
 *
 * Note that some of the functions here will be called
 * from the player or user object, so those need to be
 * public and implement their own privilege checks.
 *
 */

/*
 *
 * Ask privilege for a command path, change the privilege
 * and return to the previous menu
 *
 */

int menu_priv( string priv, string prev, string path) {

   if(!require_priv("system")) {
      error("Permission denied.");
   }
 
   if(!priv || strlen(priv) == 0) {
      this_player()->out("Privilege required for using " + path + 
         "? (* for everyone, - for no access) : ");
      this_player()->input_to_object( this_object(), "menu_priv", prev, path );
      return 1;
   }

   write("Setting privilege for " + path + " to " + priv + "\n");
   COMMAND_D->add_path( path, priv );
   return call_other(this_object(), prev, path);
}

/*
 * 
 * Ask for the name of the path to add.
 * Optionally, privilege can be specified, if it isn't
 * we'll ask for it.
 *
 */

int menu_add(string arg) {
   string path, priv;

   if(!require_priv("system")) {
      error("Permission denied.");
   }

   if (!arg) {
      this_player()->out("Path to add? (/path/ or /path/ priv, " +
         "enter to cancel) : ");
      this_player()->input_to_object(this_object(), "menu_add");
      return 1;
   }
   if((sscanf(arg,"\"%s\" %s", path, priv) != 2) && 
      (sscanf(arg,"%s %s",path,priv) != 2)) {
      path = arg;
      priv = nil;
   }

   if(path == "") {
      write("Canceled.\n");
      return menu_cmdadm();
   }

   if(path[0] != '/') {
      write("Path must start with a '/'.\n");
      return menu_add( nil );
   }

   path = trailing_slash( path );

   if(file_exists(path) != -1) {
      write("No such directory: " + path + "\n");
      return menu_add(nil);
   }

   if( priv ) {
      write("Adding path " + path + " with privilege " + priv + ".\n");
      COMMAND_D->add_path(path,priv);
      return menu_cmdadm();
   } else {
      return menu_priv( nil, "menu_cmdadm", path );
   }
}

/*
 *
 * Ask for confirmation for removing a command path.
 *
 */

int menu_remove( string str, string arg ) {
   if(!require_priv("system")) {
      error("Permission denied.");
   }
   if (str == "y" || str == "Y") {
      write("Removing command path " + arg + ".\n");
      COMMAND_D->remove_path(arg);
      write("Ok.\n");
      return menu_cmdadm();
   } else if (str == "n" || str == "N") {
      write("Aborted.\n");
      return 0;
   } else {
      this_player()->out("Remove cmdpath " + arg + "? (y/n): ");
      this_player()->input_to_object( this_object(), "menu_remove", arg );
      return 1;
   }
}

/* Leave the menu system.  */
static int menu_quit() {
   write("Ok.\n");
   return 1;
}

/*
 *
 * Toplevel menu, gets all command paths from the COMMAND_D,
 * and create a small menu from that.
 *
 */
static int menu_cmdadm(varargs mixed junk...) {
   int i,sz;
   mapping cmdpriv;
   string *path;
   mixed **menu;
   string info;

   cmdpriv = COMMAND_D->query_cmdpriv();
   path = map_indices(cmdpriv);
   menu = ({ });

   for(i=0,sz=sizeof(path); i<sz; i++) {
      if (COMMAND_D->query_override(path[i])) {
         info = "override:";
      } else if (COMMAND_D->query_syspath(path[i])) {
         info = "predefined:";
      } else {
         info = "custom:";
      }
      info += cmdpriv[path[i]];

      menu += ({ ({ "" + (i+1), path[i], info, make_fcall(this_object(), 
         "menu_path", path[i]) }) });
   }
   menu += ({ ({ "a", "add a new command path", nil, make_fcall( this_object(),
      "menu_add", nil ) }) });
   menu += ({ ({ "q", "quit", nil, make_fcall( this_object(), 
      "menu_quit" ) }) });

   do_menu( "Command path administration", menu, "select a path to edit or " +
      "action to take" );
   return 2;
}

/*
 *
 * Menu for changing privileges or removing a path
 *
 */

static int menu_path(string path) {
   mapping cmdpriv;
   mixed **menu;
   int ptype; /* 0 custom, 1 override, 2 predefined */
   string header;

   ptype = ( COMMAND_D->query_override(path) | 
      ( COMMAND_D->query_syspath(path) << 1) );
   cmdpriv = COMMAND_D->query_cmdpriv();

   menu = ({ });
   if(ptype != 2) {
      menu += ({ ({ "p", "change required privilege", cmdpriv[path], 
         make_fcall( this_object(), "menu_priv", nil, "menu_path", path ) }) });
      if (ptype) {
         header = "Editing override for " + path;
         menu += ({ ({ "r", "remove privilege override", nil, 
            make_fcall(this_object(), "menu_remove", nil, path) }) });
      } else {
         header = "Editing command path " + path;
         menu += ({ ({ "r", "remove command path", nil, 
            make_fcall(this_object(), "menu_remove", nil, path) }) });
      }
   } else {
      header = "Edit predefined command path " + path;
      menu += ({ ({ "p", "create privilege override", cmdpriv[path], 
         make_fcall( this_object(), "menu_priv", nil, "menu_path", path ) }) });
   }
   menu += ({ ({ "q", "main menu", nil, make_fcall( this_object(), 
      "menu_cmdadm" ) }) });
   do_menu(header, menu);
   return 2;
}

/*
 * The command line interface.
 * Everything can be private in here except for one function that asks 
 * for confirming * removal of a path, this function will be called from 
 * player or user objects.
 */


/* Ask for confirmation for removing a command path.  */
void action_remove_yn( string str, string path ) {
   if(!require_priv("system")) {
      error("Permission denied.");
   }

   if (str && strlen(str) > 0) {
      str = lowercase( str[0..] );
      if (str == "y") {
         COMMAND_D->remove_path(path);
         write("Removed " + path + "\n");
         return;
      } else if (str == "n") {
         write("Canceled.\n");
         return;
      }
   }

   this_player()->out("Remove command path " + path + "? (y/n)");
   this_player()->input_to_object( this_object(), "action_remove_yn", path );
}

/*
 *
 * Handle delete/remove subcommands.
 * Check if the path exists and ask
 * for confirmation.
 *
 */

private int action_del_path(string str) {
   if(!str) {
      notify_fail("delete needs a path as argument");
      return 0;
   }

   str = trailing_slash( str );

   if(!COMMAND_D->cmd_path_exists(str)) {
      notify_fail("command path does not exist");
      return 0;
   }

   action_remove_yn( nil, str );
   return 1;
}

/* Handle the list/show command */
private int action_list_path() {
   int i, sz, ptype, len;
   string *path, r;
   mapping cmdpriv;

   cmdpriv = COMMAND_D->query_cmdpriv();
   path = map_indices(cmdpriv);

   /* determine the longest command path name */
   for(i=0,sz=sizeof(path); i<sz; i++) {
      if(strlen(path[i]) > len) {
         len = strlen(path[i]);
      }
   }

   len += 2;

   for(i=0; i<sz; i++) {
      ptype = (COMMAND_D->query_override(path[i]) | (COMMAND_D->query_syspath(path[i]) << 1));
      r = padstr(path[i], len) + padstr("(" + (!(ptype & 3) ? "custom" : (ptype & 1) ? "override" : "predefined" ) + ")", 14);
      r += " : " + cmdpriv[path[i]];
      write(r + "\n");
   }
   return 1;
}

/*
 *
 * Handle the add and priv commands.
 *
 * ch will be set to 0 for the add command, 1 for the priv command.
 *
 */

private int action_add_path(string str, int ch) {
   string path, priv;

   if(!str || ((sscanf(str, "%s %s", path, priv) != 2) && 
      (sscanf(str, "\"%s\" %s", path, priv) != 2))) {
      notify_fail("add needs a path and a privilege as arguments");
      return 0;
   }

   if(path[0] != '/') {
      notify_fail("path needs to start with a /");
      return 0;
   }

   path = trailing_slash( path );

   if(!ch && COMMAND_D->cmd_path_exists( path )) {
      notify_fail("command path already exists");
      return 0;
   } else if(ch && !COMMAND_D->cmd_path_exists( path )) {
      notify_fail("command path does not exist");
      return 0;
   }

   if(file_exists(path) != -1) {
      notify_fail("path does not exist");
      return 0;
   }

   COMMAND_D->add_path( path, priv );
   if(ch) {
      write("Changed privilege for " + path + " to " + priv + "\n");
   } else {
      write("Added command path " + path + " with privilege " + priv + "\n");
   }
   return 1;
}

/*
 *
 * Parse argument to command and possible arguments
 * and call appropriate functions for each command.
 *
 * Commands return 1 on success or 0 on failure, when
 * they fail, check if they left any failure message,
 * display it, and then display the usage message.
 *
 */
 
static void main(string str) {
   int r;
   string cmd, arg;

   /* only ever try this when we got at least 2 chars (shortest possible command) */
   if(str && strlen(str) > 1) {
      if(sscanf(str, "%s %s", cmd, arg) != 2) {
         cmd = str;
      }

      /* commands cannot be shorter then 2 chars */
      if (strlen(cmd) > 1) {
         switch(cmd[0..1]) {
            case "ad" : r = action_add_path( arg, 0 );
                        break;
            case "re" :                                           
            case "de" : r = action_del_path( arg );
                        break;
            case "pr" : r = action_add_path( arg, 1 );
                        break;
            case "sh" :
            case "li" : if (arg) {
                           notify_fail(cmd + " does not take any arguments");
                           r = 0;
                        } else {
                           r = action_list_path();
                        }
                        break;
            case "me" : if (arg) {
                           notify_fail(cmd + " does not take any arguments");
                           r = 0;
                        } else {
                           menu_cmdadm();
                           r = 1;
                        }
                        break;
            case "-h" :
            case "he" : r = 0;
                        break;
            default   : notify_fail("unknown command");
                        r = 0;
                        break;
         }
      } else {
         r = 0;
         notify_fail("unknown command");
      }
   } else if (str && str != "") {
      r = 0;
      notify_fail("unknown command");
   }
   

   /* check if the command completed, if not display optional error and usage info *
    * note, this also handles the help and -h commands                             */
   if (r) {
      return;
   } else if (str && str != "") {
      string *err;

      str = query_notify_fail();

      if(str) {
         err = ({ ANSI_D->parse_colors("%^RED%^BOLD%^Error: " + str + "%^RESET%^") });
      } else {
         err = ({ });
      }
      err += map_array(query_usage(), "parse_colors", ANSI_D);
      this_player()->more( err );
   } else {
      menu_cmdadm();
   }
}
