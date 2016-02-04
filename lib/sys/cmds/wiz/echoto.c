inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: echoto [-h] [player] MSG" });
   lines += ({ " " });
   lines += ({ "Echo a message MSG to the player specified." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techoto sirdude You hear a odd noise." });

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
   add_also("wiz", "rsay");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

static void main(string who) {
   object *usr;
   int i, flag;
   string msg;

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

   sscanf(who, "%s %s", who, msg);

   usr = USER_D->query_players();
   flag = 0;
   for (i = 0; i < sizeof(usr); i++) {
      if (usr[i]->query_name() == who) {
         usr[i]->message("\n" + msg + "\n");
         write("You echo to " + who + ": '" + msg + "'\n");
         flag = 1;
      }
   }

   if (flag == 0) {
      write("You can't find " + who + ".\n");
   }
}
