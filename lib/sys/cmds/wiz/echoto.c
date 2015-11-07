inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: echoto [-h] [player] MSG" });
   lines += ({ " " });
   lines += ({ "Echo a message MSG to the player specified." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techoto sirdude You hear a odd noise." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, chan, echo, emote, rsay, shout, ssay, say, " +
      "sysmsg, tell, translate, whisper, wizcall" });

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   return lines;
}

static void main(string who) {
   object *usr;
   int i, flag;
   string msg;

   if (empty_str(who)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(who, "-%s", who)) {
      this_player()->more(usage());
      return;
   }

   sscanf(who, "%s %s", who, msg);

   usr = USER_D->query_players();
   flag = 0;
   for (i = 0; i < sizeof(usr); i++) {
      if (usr[i]->query_name() == who) {
         usr[i]->message("\n" + msg + "\n");
         write("You echo to " + who + ": '" + msg + "'\n");
         flag = 1;
      }
   }

   if (flag == 0) {
      write("You can't find " + who + ".\n");
   }
}
