/* Fudge created, *  03.08.98  Satch added 'reason' for shutdown.  */
string reason;

void usage() {
   write("Usage: shutdown [-h] [now|MINUTES] REASON\n");
   write("Shutdown the server now or MINUTES minutes later.\n");
   write("REASON is a message why the shutdown is needed.\n");
   write("Note: there is no way to stop a shutdown.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tshutdown 5 were upgrading the server's memory.\n");
   write("\tshutdown now sorry were experiencing major problems.\n");
   write("See also: clone, dumpstate, rebuild, update, warmboot\n");
}

void do_shutdown() {
   string *usrs;
   object *objs;
   int i, max, j, jmax;

   usrs = OBJECT_D->query_object_owners();
   max = sizeof(usrs);
   for (i = 0; i < max; i++) {
      objs = OBJECT_D->query_objects_by_owner(usrs[i]);
      jmax = sizeof(objs);
      for(j=0; j< jmax; j++) {
         if (objs[j]->is_player()) {
            objs[j]->message("Shutdown initiated by : " +
               this_player()->query_Name() + "\n");
            objs[j]->message("Game driver tells you: " +
               "Shutting down immediately!\n");
            objs[j]->message("  Reason : " + reason + "\n");
         }
         objs[j]->save_me();
      }
   }
   shutdown();
}

void countdown(int mins) {
   object *usrs;
   int i;

   usrs = USER_D->query_players();
  
   if (mins < 0) {
      usage();
      return;
   } else if (mins == 0) {
      do_shutdown();
   } else {
      for (i = 0; i < sizeof(usrs); i++) {
	 usrs[i]->message("Shutdown initiated by : " +
	    this_player()->query_Name() + "\n");
	 usrs[i]->message("Game driver tells you: " +
	    "Shutting down in " + mins + " minutes!\n");
	 usrs[i]->message("  Reason : " + reason + "\n");
      }
      call_out("countdown", 60, mins - 1);
   }
}

void main(string arg) {
   object *usrs;
   string time;

   if (!arg || arg == "") {
      usage();
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   if (sscanf(arg, "%s %s", time, reason) != 2) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You need admin permissions to do that.");
      return;
   }

   if (lowercase(time) == "now") {
      LOG_D->write_log("shutdown", ctime(time()) + ": " +
	 this_player()->query_Name() + " forced a shutdown.\n" + "REASON: "
	 + reason + "\n");
      do_shutdown();
   } else {
      LOG_D->write_log("shutdown", ctime(time()) + ": " +
	 this_player()->query_Name() + " forced a shutdown.\n" + "REASON: " +
	 reason + "\n");
      countdown(str2val(time));
   }
}
