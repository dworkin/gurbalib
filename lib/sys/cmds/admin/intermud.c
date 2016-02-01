inherit M_COMMAND;

#include <ports.h>

#define grammar "whitespace=/[ 	]/ " + \
                "command=/restart/ " + \
                "command=/status/  " + \
                "command=/stop/ " + \
                "command=/start/ " + \
                "command=/enable/ " + \
                "command=/disable/ " + \
                "command=/switch/ " + \
                "command=/default/ " + \
                "arg=/[a-zA-Z0-9*]*/ " + \
                "arguments: command " + \
                "arguments: command arg"

string *usage(void) {
   string *lines;

   lines = ({ "Usage: intermud [-h] <command> [arg]" });
   lines += ({ " " });
   lines += ({ "An interface to the intermud connection service." });
   lines += ({ "Valid commands:" });
   lines += ({ "  - status" });
   lines += ({ "    Shows information on the current intermud connection" });
   lines += ({ "  - stop" });
   lines += ({ "    Stops the current connection and unloads the intermud " +
      "service" });
   lines += ({ "  - start" });
   lines += ({ "    Loads the intermud service and starts a connection " +
      "(if enabled)" });
   lines += ({ "  - enable" });
   lines += ({ "    Enables intermud 3 connections" });
   lines += ({ "  - disable" });
   lines += ({ "    Disables intermud 3 connections" });
   lines += ({ "  - default [name]" });
   lines += ({ "    Displays the default router (and sets it if name " +
      "is provided" });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tintermud start" });
   lines += ({ "\tintermud status" });
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "chan");
   add_also("player", "mudlist");
   add_also("player", "rwho");
}

static int check_istat(void) {
   if (!find_object(IMUD_D)) {
      return 0;
   } else {
      return 1 + IMUD_D->query_connected();
   }
}

void display_istat(void) {
   int s;
   string r;

   s = check_istat();

   switch (s) {
      case 0:
         r = "not loaded";
         break;
      case 1:
         r = "loaded and offline\n";
         if (IMUD_D->query_enabled()) {
            r += "I3 is enabled\n";
         } else {
            r += "I3 is disabled\n";
         }
         r += "Default router: " + IMUD_D->query_default_router() + "\n"; 
         break;
      case 2:
         r = "loaded and online\n";
         r += "Connected to " + IMUD_D->query_current_router_name() + " (" +
            IMUD_D->query_current_router_ip() + ")\n";
         break;
   }
   write("I3 status: " + r + "\n");
}

static void main(string str) {
   mixed *args;
   string error;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (error = catch(args = parse_string(grammar, str))) {
      int pos;

      if (sscanf(error, "Bad token at offset %d", pos) == 1) {
         write("Invalid character " + str[pos..pos] + " at position " + pos +
            ".");
         return;
      } else {
         rethrow();
      }
   }

   if (!args) {
      this_player()->more(usage());
      return;
   }

   switch (args[0]) {
      case "restart":
         if (!find_object(IMUD_D)) {
            write("IMUD_D is not loaded");
         } else if (!IMUD_D->query_enabled()) {
            write("IMUD_D is not enabled");
         } else {
            if (IMUD_D->query_connection()) {
               IMUD_D->query_connection()->set_mode(MODE_DISCONNECT);
            }
         }
         break;
      case "status":
         display_istat();
         break;
      case "enable":
         IMUD_D->enable_i3();
         display_istat();
         break;
      case "disable":
         if (!find_object(IMUD_D)) {
            write("IMUD_D is not loaded");
         } else {
            IMUD_D->disable_i3();
            display_istat();
         }
         break;
      case "start":
         if (find_object(IMUD_D)) {
            write("Already active");
         } else {
            call_other(IMUD_D, "???");
            write("IMUD_D loaded and starting");
         }
         break;
      case "stop":
         if (!find_object(IMUD_D)) {
            write("IMUD_D is not active");
         } else {
            destruct_object(find_object(IMUD_D));
            write("IMUD_D unloaded");
         }
         break;
      case "switch":
         if (!find_object(IMUD_D)) {
            write("IMUD_D is not active");
         } else {
            IMUD_D->switch_router();
         }
         break;
      case "default":
         if (!find_object(IMUD_D)) {
            write("IMUD_D is not active");
         } else {
            if (sizeof(args) > 1) {
               IMUD_D->set_default_router(args[1]);
            }
            write("Default router: " + IMUD_D->query_default_router());
         }
         break;
   }
}
