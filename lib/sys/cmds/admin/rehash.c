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
   lines += ({ "\talias, aliasadmin, cmds, cmdadm, coloradm, emote, " +
      "emoteadm, help, " });

   this_player()->more(lines);
}

static void main(string str) {

   if (!require_priv("system")) {
      write("You need admin permissions to do that.");
      return;
   }

   if (str && str != "") {
      usage();
   } else {
      COMMAND_D->rehash();
      write("Re evaluating command paths.\n");
      write(COMMAND_D->cmdstats());
      write("Done.\n"); 
   }
}
