inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: wall [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Tell everyone on the mud: MSG." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-w\tRestrict the MSG to sending only to wizards, " +
      "not normal players." });
   lines += ({ "Examples:" });
   lines += ({ "\twall We are upgrading the server in 10 minutes." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, ssay, say, " +
      "sysmsg, tell, translate, whisper, wizcall" });

   this_player()->more(lines);
}

static void main(string str) {
   object *users;
   int i, max;

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-w %s", str)) {
      if (!require_priv("system")) {
	 write("You need admin permissions to do that.");
	 return;
      }

      users = USER_D->query_wizards();

      max = sizeof(users);
      for (i = 0; i < max; i++) {
	 users[i]->message("WALL from " +
	    this_player()->query_Name() + ": " + str + "\n");
      }

      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   users = USER_D->query_players();
   max = sizeof(users);
   for (i = 0; i < max; i++) {
      users[i]->message("WALL from " +
	 this_player()->query_Name() + ": " + str + "\n");
   }
}
