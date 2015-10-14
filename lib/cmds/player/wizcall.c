inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: wizcall [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Notify all active wizards that you need help." });
   lines += ({ "You should have a good reason to bug them. :)" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twizcall I need help I'm stuck in a room I can not get " + 
      "out of." });
   lines += ({ "\twizcall I found a bug in the look command." });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, " +
         "ssay, say, sysmsg, tell, translate, whisper" });
   } else {
      lines += ({ "\tbug, chan, emote, rsay, say, shout, tell, whisper" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   return lines;
}

static void main(string str) {
   int i, flag;
   object *usrs;

   flag = 0;

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   usrs = USER_D->query_wizards();

   if (str != "") {
      for (i = 0; i < sizeof(usrs); i++) {
         if (query_wizard(usrs[i])) {
            usrs[i]->message("%^RED%^" + "" + this_player()->query_Name() +
               " wizcalls: %^RESET%^" + str + "\n");
            LOG_D->write_log("wizcall", this_player()->query_Name() + 
               " on " + ctime(time()) + ": " + str + "\n");
         }
      }
   } else {
      write("The almighty wizards would like a reason for your attempting " +
         "to summon them.");
      flag = 1;
   }

   if (flag == 0) {
      write("You call for help.");
   }
}

