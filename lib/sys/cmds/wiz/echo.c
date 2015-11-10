inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: echo [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Echo a message MSG to the room." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techo something makes a noise in the corner." });
   lines += ({ "See also:" });

   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echoto, emote, rsay, say, shout, " +
         "ssay, sysmsg, tell, translate, whisper, wizcall, wizlog" });
   }
   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }


   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   return lines;
}

static void main(string str) {

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   this_player()->query_environment()->tell_room(this_player(), "\n" + str +
      "\n");
   write("You echo to the room: '" + str + "'.\n");
}
