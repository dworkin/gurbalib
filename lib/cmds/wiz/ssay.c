void usage() {
   write("Usage: ssay [-h] HOW|WHAT\n");
   write("Ssay is short for SuperSay, it will allow you to ");
   write("say WHAT to WHO. But do it HOW.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: say, tell, whisper, emote\n");
   write("Examples:\n");
   write("\t> ssay sleepily drones|Hiya\n");
   write("\tAphex sleepily drones: Hiya\n");
   write("\t> ssay kicks Dran in the pants and says|Muahhahahaha!\n");
   write("\tAphex kicks Dran in the pants and says: Muahhahahaha!\n");
   write("See also: emote, rsay, say, shout, tell, translate, whisper\n");
}

void main(string str) {
   int i;
   string how;			/*It's not what you say, but how you say it. */
   string what;			/*But what you say is important too. */

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
