void usage() {
   string *lines;

   lines = ({ "Usage: sysmsg [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Send a system message MSG to everyone on the mud." });
   lines += ({ "Note: these messages are logged, do not abuse it." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsysmsg Let the games begin." });
   lines += ({ "See also:" });

   lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, ssay, say, " +
      "tell, translate, whisper, wizcall" });

   this_player()->more(lines);
}

void main(string msg) {
   object *usr;
   int i;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!msg || (msg == "")) {
      usage();
      return;
   } else if (sscanf(msg, "-%s", msg)) {
      usage();
      return;
   } else {
      usr = USER_D->query_players();

      for (i = 0; i < sizeof(usr); i++) {
	 usr[i]->message("\n" +
	    "%^RED%^System Message from %^GREEN%^" +
	    this_player()->query_Name() +
	    "%^RED%^ on %^WHITE%^" + ctime(time()) + "%^RED%^:%^RESET%^\n");
	 usr[i]->message("\"" + msg + "\"");
      }
      LOG_D->write_log("sysmsg", this_player()->query_Name() +
	 " on " + ctime(time()) + ": \"" + msg + "\"\n");
   }
}
