void usage() {
   string *lines;

   lines = ({ "Usage: wizcall [-h] MSG" });
   lines += ({ "Notify all active wizards that you need help." });
   lines += ({ "You should have a good reason to bug them. :)" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twizcall I need help I'm stuck in a room I can not get " +
      "out of." });
   lines += ({ "\twizcall I found a bug in the look command." });
   if (query_wizard(this_player())) {
      lines += ({ "See also: bug, emote, rsay, say, shout, ssay, tell, " +
         "translate, whisper" });
   } else {
      lines += ({ "See also: bug, emote, rsay, say, shout, tell, whisper" });
   }

   this_player()->more(lines);
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
