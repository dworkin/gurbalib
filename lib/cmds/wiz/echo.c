void usage() {
   string *lines;

   lines = ({ "Usage: echo [-h] MSG\n");
   lines += ({ " " });
   lines += ({ "Echo a message MSG to the room.\n");
   lines += ({ " " });
   lines += ({ "Options:\n");
   lines += ({ "\t-h\tHelp, this usage message.\n");
   lines += ({ "Examples:" });
   lines += ({ "\techo something makes a noise in the corner." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, echoto, emote, rsay, say, shout, ssay, tell, " +
      "translate, whisper, wizcall" });

   this_player()->more(lines);
}

void main(string str) {
   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   this_player()->query_environment()->tell_room(this_player(), "\n" + str +
      "\n");
   write("You echo to the room: '" + str + "'.\n");
}
