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
   lines += ({ "\tbug, chan, echoto, emote, rsay, shout, ssay, say, " +
      "sysmsg, tell, translate, whisper, wizcall" });

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
