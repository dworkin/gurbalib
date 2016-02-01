inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: sysmsg [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Send a system message MSG to everyone on the mud." });
   lines += ({ "Note: these messages are logged, do not abuse it." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsysmsg Let the games begin." });

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
   add_also("wiz", "ssay");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

static void main(string msg) {
   object *usr;
   int i, sz;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(msg)) {
      this_player()->more(usage());
      return;
   } else if (sscanf(msg, "-%s", msg)) {
      this_player()->more(usage());
      return;
   } else {
      usr = USER_D->query_players();

      sz = sizeof(usr);
      for (i = 0; i < sz; i++) {
         usr[i]->message("\n" +
            "%^RED%^System Message from %^GREEN%^" +
            this_player()->query_Name() +
            "%^RED%^ on %^WHITE%^" + ctime(time()) + "%^RED%^:%^RESET%^\n");
         usr[i]->message("\"" + msg + "\"");
      }
      LOG_D->write_log("sysmsg", this_player()->query_Name() +
         " on " + ctime(time()) + ": \"" + msg + "\"\n");
   }
}
