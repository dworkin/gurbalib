inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: shout [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Send MSG to all players on the mud.  This command should " +
      "only be used SPARINGLY." });
   lines += ({ "Don't abuse it or you'll lose it." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tshout I am the fluffy bunny king!" });
   lines += ({ "\tshout no your not!" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, ssay, say, " +
         "sysmsg, tell, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tbug, chan, emote, rsay, say, tell, whisper, " + 
         "wizcall" });
   }

   this_player()->more(lines);
}

static void main(string str) {
   int i;
   object *usrs;

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->query_muzzle()) {
      write("A magical muzzle has been placed on you, you can not shout.\n");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " tries to shout but " +
         "the words will not come out.\n");
      return;
   }

   usrs = players();

   for (i = 0; i < sizeof(usrs); i++) {
      usrs[i]->message("%^RED%^" + "" +
         this_player()->query_Name() + " shouts: %^RESET%^" + str + "\n");
   }
}
