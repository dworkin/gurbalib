inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: motd [-h]" });
   lines += ({ "" });
   lines += ({ "Allows you to view the motd(Message of the day)." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmotd" });

   lines += get_alsos();

   return lines;
}

setup_alsos() {
   add_also("player", "fortune");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      string *lines;

      lines = explode(TELNET_D->query_motd(), "\n");
      this_player()->more(lines);
   } else {
      this_player()->more(usage());
   }
}
