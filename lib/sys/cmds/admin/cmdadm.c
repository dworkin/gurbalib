/*
 * menu interface for managing the command system.
 *
 * August 2013, Aidil@Way of the Force
 *
 */

inherit M_COMMAND;
inherit "/sys/lib/menu";

static int menu_cmdadm(varargs mixed junk...);

string *query_usage() {
   string *lines;
   lines = ({ "Usage: cmdadm" });
   return lines;
}

void usage() {
   this_player()->more(query_usage());
}
   
private string trailing_slash( string str ) {
   if(str && strlen(str) && str[strlen(str)-1] != '/') {
      str += "/";
   }
   return str;
}

int menu_priv( string priv, string *arg) {
   string path, prev;

   if(!require_priv("system")) {
      error("Permission denied.");
   }
 
   ({ path, prev }) = arg;

   if(!priv || strlen(priv) == 0) {
      this_player()->out("Privilege required for using " + path + "? (* for everyone) : ");
      this_player()->input_to_object( this_object(), "menu_priv", arg );
      return 1;
   }

   write("Setting privilege for " + path + " to " + priv + "\n");
   COMMAND_D->add_path( path, priv );
   return call_other(this_object(), prev, path);
}

int menu_add(string arg) {
   string path, priv;

   if(!require_priv("system")) {
      error("Permission denied.");
   }

   if (!arg) {
      this_player()->out("Path to add? (/path/ or /path/ priv) : ");
      this_player()->input_to_object(this_object(), "menu_add");
      return 1;
   }
   if((sscanf(arg,"\"%s\" %s", path, priv) != 2) && (sscanf(arg,"%s %s",path,priv) != 2)) {
      path = arg;
      priv = nil;
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
      return menu_priv( nil, ({ path, "menu_cmdadm" }) );
   }
}

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

static int menu_quit() {
   write("Ok.\n");
   return 1;
}

static int menu_cmdadm(varargs mixed junk...) {
   int i,sz;
   mapping cmdpriv;
   string *path;
   mixed **menu;

   cmdpriv = COMMAND_D->query_cmdpriv();
   path = map_indices(cmdpriv);
   menu = ({ });

   for(i=0,sz=sizeof(path); i<sz; i++) {
      menu += ({ ({ "" + (i+1), path[i], cmdpriv[path[i]], make_fcall(this_object(), "menu_path", path[i]) }) });
   }
   menu += ({ ({ "a", "add a new command path", nil, make_fcall( this_object(), "menu_add", nil ) }) });
   menu += ({ ({ "q", "quit", nil, make_fcall( this_object(), "menu_quit" ) }) });

   do_menu( "Command path administration", menu, "select a path to edit or action to take" );
   return 2;
}

static int menu_path(string path) {
   mapping cmdpriv;

   cmdpriv = COMMAND_D->query_cmdpriv();
   do_menu( "Edit " + path, 
      ({
         ({ "p", "change required privilege", cmdpriv[path], make_fcall( this_object(), "menu_priv", nil, ({ path, "menu_path" }) ) }),
         ({ "r", "remove command path", nil, make_fcall(this_object(), "menu_remove", nil, path) }),
         ({ "q", "main menu", nil, make_fcall( this_object(), "menu_cmdadm" ) })
      })
   );
   return 2;
}
 
static void main(string str) {
   menu_cmdadm();
}
