void usage() {
   write("Usage: sysmsg [-h] MSG\n");
   write("Send a system message MSG to everyone on the mud.\n");
   write("Note: these messages are logged.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string msg) {
   object *usr;
   int i;

   usr = USER_D->query_players();

   if (!msg || (msg == "")) {
      usage();
      return;
   } else if (sscanf(msg, "-%s", msg)) {
      usage();
      return;
   } else {
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
