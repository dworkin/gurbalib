inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: set [-h] [VAR VALUE]" });
   lines += ({ " " });
   lines += ({ "Make changes to the settings for your account." });
   lines += ({ "If no VAR VALUE pair is given print your current settings."
      });
   lines += ({ "Some variables you can set:" });
   lines += ({ "\theight\t\theight of your screen.  "+
    "Set to 0 for max height, 1 for default height, or use custom value." });
   lines += ({ "\twidth\t\twidth of your screen." });
   lines += ({ "\tprompt\t\tYour prompt." });
   if (!query_guest(this_player()->query_name() ) ) {
      lines += ({ "\trealname\t\tYour real name." });
      lines += ({ "\email\t\tYour email address." });
      lines += ({ "\twww\t\tYour website." });
   }
   if (query_wizard(this_player() ) ) {
      lines += ({ "\tstart\t\tyour starting room." });
      lines += ({ "\thidden\t\tSet to 1 if you want to hide your login from " +
         "users." });
      lines += ({ "\tautoload\tSet to 1 if you want to save your equipment " +
         "on quit." });
      lines += ({ "\tsave_on_quit\tSet to 1 if you want to start where you " +
         "last quit." });
      lines += ({ "\tquit_message\tSet your quit message.  " +
         "Example: $N $vquit." });
      lines += ({ "\tdebug_commands\tSet to 1 if you want debugging of " +
         "commands." });
      lines += ({ "\tverbose_errors\tSet to 1 if you want longer error " +
         "codes." });
      lines += ({ "\tdisplay_caught\tSet to 1 if you want to show caught " +
         "runtime errors." });
   }
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tset width 50" });
   lines += ({ "\tset email foo@bar.com" });
   this_player()->more(lines);
}

void list_vars(void) {
   string name, *names;
   int i;

   names = ({ "height", "width", "prompt" });
   if (!query_guest(this_player()->query_name() ) ) {
      names += ({ "realname", "email", "website" });
      }
   if (query_wizard(this_player() ) ) {
      names += ({ "start_room", "hidden", "autoload", "save_on_quit", 
         "quit_message", "debug_commands", "verbose_errors",
         "display_caught" });
   }
   for (i = 0; i < sizeof(names); i++) {
      out_unmod(names[i] + "=" + call_other(this_player(), "query_" +
         names[i]) + "\n");
   }
}

static void main(string str) {
   string name, value;
   int i;

   if (empty_str(str)) {
      list_vars();
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else if ((sscanf(str, "%s %s", name, value) != 2) &&
      (sscanf(str, "%s=%s", name, value) != 2)) {
      usage();
      return;
   } else {
        if (value == "on") {
           value = "1";
        } else if (value == "off") {
           value = "0";
         }
        switch(name) {
           case "height":
           case "width":
           case "prompt":
              break;
           case "realname":
           case "email":
           case "website":
              if (query_guest(this_player()->query_name() ) ) {
                 write("You must be logged in with a character.");
              return;
              }
              break;
           case "hidden":
           case "autoload":
           case "save_on_quit":
           case "debug_commands":
           case "verbose_errors":
           case "display_caught":
              if (value != "0" && value != "1") {
                 write("The argument for " + name + " must be 1 or 0.");
                 return;
              }
           case "quit_message":
           case "start_room":
              if (query_wizard(this_player() ) )  {
                 break;
              }
           default:
              write("Invalid setting name \"" + name + "\".\n\n");
              usage();
              return;
        }
      write("Ok.");
      if (str2val(value) != -1) {                     
         /* We've got a value */
         call_other(this_player(), "set_" + name, str2val(value) );
      } else {
         call_other(this_player(), "set_" + name, value);
      }
   }
}
