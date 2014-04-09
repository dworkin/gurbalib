inherit M_COMMAND;

void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\talias, aliasadmin, cmds, cmdadm, coloradm, domain, emote, " +
      "emoteadm, help" });

   this_player()->more(lines);
}

static void main(string str) {

   if (!empty_str(str)) {
      usage();
   } else {
      COMMAND_D->rehash();
      write("Re evaluating command paths.\n");
      write(COMMAND_D->cmdstats());
      write("Done.\n"); 
   }
}
