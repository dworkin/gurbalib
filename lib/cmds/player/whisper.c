inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: whisper [-h] WHO MSG" });
   lines += ({ "" });
   lines += ({ "Whisper a message MSG to WHO" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twhisper sirdude you are cool." });
   lines += ({ "\twhisper guest Hi how are you?" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

static void main(string who) {
   object *usr;
   int i, flag;
   string what;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(who)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(who, "-%s", who)) {
      this_player()->more(usage());
      return;
   }

   sscanf(who, "%s %s", who, what);

   if (what && (what != "")) {
      what = capitalize(what);
   }

   usr = USER_D->query_players();
   flag = 0;
   for (i = 0; i < sizeof(usr); i++) {
      if ((usr[i]->query_environment() == this_environment()) &&
         (usr[i]->query_name() == who)) {
         usr[i]->message(this_player()->query_Name() +
            " whispers to you: " + what + "\n");
         write("You whisper to " + capitalize(who) + ": " + what + "\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() +
            " whispers something to " + capitalize(who) + ".\n", usr[i]);
         flag = 1;
      }
   }

   if (!flag) {
      write("Who did you want to whisper to?\n");
   }
}

