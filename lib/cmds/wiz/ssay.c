void usage() {
   string *lines;

   lines = ({ "Usage: ssay [-h] HOW|WHAT" });
   lines += ({ " " });
   lines += ({ "Ssay is short for SuperSay, it will allow you to " });
   lines += ({ "say WHAT to WHO. But do it HOW." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tssay sleepily drones|Hiya" });
   lines += ({ "\tssay kicks Dran in the pants and says|Muahhahahaha!" });
   lines += ({ "See also:" });
   lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, say, " +
      "sysmsg, tell, translate, whisper, wizcall" });

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

void main(string str) {
   int i;
   string how;			/*It's not what you say, but how you say it. */
   string what;			/*But what you say is important too. */

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   /* Strip trailing whitespaces */
   for (i = strlen(str) - 1; i > 0; i--) {
      if (str[i] != ' ')
	 break;
      str = str[0..(i - 1)];
   }

   if (sscanf(str, "%s|%s", how, what) != 2) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str != "") {

      switch (what[strlen(what) - 1]) {
	 case '.':
	 case '?':
	 case '!':
	 case ',':
	    break;
	 default:
	    what += ".";
      }

      this_player()->query_environment()->tell_room(nil, "%^GREEN%^" +
	 this_player()->query_Name() + " " + how +
	 ": %^RESET%^" + capitalize(what) + "\n");
   } else {
      usage();
      return;
   }
}
