inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: echo [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Echo a message MSG to the room." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techo something makes a noise in the corner." });

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

   add_also("wiz", "echoto");
   add_also("wiz", "rsay");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}


static void main(string str) {
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

   this_player()->query_environment()->tell_room(this_player(), "\n" + str +
      "\n");
   write("You echo to the room: '" + str + "'.\n");
}
