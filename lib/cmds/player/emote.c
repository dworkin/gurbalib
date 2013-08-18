inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: emote [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Send a message MSG to everyone in the room." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\temote does a flip!" });
   lines += ({ "\temote beep sirdude" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, rsay, shout, ssay, say, " +
         "sysmsg, tell, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tbug, chan, rsay, say, shout, tell, whisper, " +
         "wizcall" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

static void main(string str) {
   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!this_player()->is_player() || query_wizard(this_player())) {
      this_player()->query_environment()->tell_room(nil,
	 this_player()->query_Name() + " " + str);
   } else {
      this_player()->query_environment()->tell_room(nil, "-> " +
	 this_player()->query_Name() + " " + str);
   }
}
