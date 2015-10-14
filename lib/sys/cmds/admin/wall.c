inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: wall [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Tell everyone on the mud: MSG." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-w\tRestrict sending the MSG to only wizards or higher." });
   lines += ({ "Examples:" });
   lines += ({ "\twall We are upgrading the server in 10 minutes." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, ssay, say, " +
      "sysmsg, tell, translate, whisper, wizcall" });

   return lines;
}

static void main(string str) {
   object *users;
   int i, max;

   if (empty_str(str)) {
      this_player()->more(usage());
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
      this_player()->more(usage());
      return;
   }

   users = USER_D->query_players();
   max = sizeof(users);
   for (i = 0; i < max; i++) {
      users[i]->message("WALL from " +
	 this_player()->query_Name() + ": " + str + "\n");
   }
}
