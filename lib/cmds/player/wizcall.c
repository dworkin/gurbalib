void usage() {
   write("Usage: wizcall [-h] MSG\n");
   write("Notify all active wizards that you need help.\n");
   write("You should have a good reason to bug them. :)\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\twizcall I need help I'm stuck in a room I can not get out of.\n");
   write("\twizcall I found a bug in the look command.\n");
   if (query_wizard(this_player())) {
      write("See also: bug, emote, rsay, say, shout, ssay, tell, translate, " +
         "whisper\n");
   } else {
      write("See also: bug, emote, rsay, say, shout, tell, whisper\n");
   }
}

void main(string str) {
   int i;
   int flag;
   object *usrs;
   flag = 0;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   usrs = USER_D->query_wizards();

   if (str != "") {
      for (i = 0; i < sizeof(usrs); i++) {
	 if (query_wizard(usrs[i])) {
	    usrs[i]->message("%^RED%^" + "" + this_player()->query_Name() +
	       " wizcalls: %^RESET%^" + str + "\n");
	    LOG_D->write_log("wizcall", this_player()->query_Name() + " on " +
	       ctime(time()) + ": " + str + "\n");
	 }
      }
   } else {
      write ("The almighty wizards would like a reason for your attempting " +
         "to summon them.");
      flag = 1;
   }
   if (flag == 0) {
      write("You call for help.");
   }
}
