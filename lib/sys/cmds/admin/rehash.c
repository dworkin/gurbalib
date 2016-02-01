inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: rehash [-h]" });
   lines += ({ " " });
   lines += ({ "Re evaluate the command paths to add/remove commands." });
   lines += ({ "Any time you add/remove a command or a command path you will " +
      "need to run this." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trehash" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "cmds");
   add_also("player", "emote");
   add_also("player", "help");

   add_also("wiz", "aliasadm");
   add_also("wiz", "emoteadm");

   add_also("admin", "cmdadm");
   add_also("admin", "coloradm");
   add_also("admin", "domain");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
   } else {
      COMMAND_D->rehash();
      write("Re evaluating command paths.\n");
      write(COMMAND_D->cmdstats());
      write("Done.\n"); 
   }
}
