inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: ssay [-h] HOW|WHAT" });
   lines += ({ " " });
   lines += ({ "Ssay is short for SuperSay, it will allow you to " });
   lines += ({ "say WHAT to WHO. But do it HOW." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tssay sleepily drones|Hiya" });
   lines += ({ "\tssay kicks Dran in the pants and says|Muahhahahaha!" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "rsay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

static void main(string str) {
   int i;
   string how;          /*It's not what you say, but how you say it. */
   string what;         /*But what you say is important too. */

   if (!alsos) {
      setup_alsos();
   }

   /* Strip trailing whitespaces */
   for (i = strlen(str) - 1; i > 0; i--) {
      if (str[i] != ' ') {
         break;
      }
      str = str[0..(i - 1)];
   }

   if (sscanf(str, "%s|%s", how, what) != 2) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (str != "") {

      switch (what[strlen(what) - 1]) {
         case '.':
         case '?':
         case '!':
         case ',':
            break;
         default:
            what += ".";
      }

      this_player()->query_environment()->tell_room(nil, "%^GREEN%^" +
         this_player()->query_Name() + " " + how +
         ": %^RESET%^" + capitalize(what) + "\n");
   } else {
      this_player()->more(usage());
      return;
   }
}
