inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: emote [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Send a message MSG to everyone in the room." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\temote does a flip!" });
   lines += ({ "\temote beep sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
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

   if (!this_player()->is_player() || query_wizard(this_player())) {
      this_player()->query_environment()->tell_room(nil,
      this_player()->query_Name() + " " + str);
   } else {
      this_player()->query_environment()->tell_room(nil, "-> " +
         this_player()->query_Name() + " " + str);
   }
}
