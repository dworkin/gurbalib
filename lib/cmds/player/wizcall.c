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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

static void main(string str) {
   int i, flag;
   object *usrs;

   flag = 0;

   if (!alsos) {
      setup_alsos();
   }

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

