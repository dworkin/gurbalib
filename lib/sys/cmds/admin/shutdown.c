/* Fudge created, *  03.08.98  Satch added 'reason' for shutdown.  */

inherit M_COMMAND;

string reason;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: shutdown [-h] [now|MINUTES] REASON" });
   lines += ({ "" });
   lines += ({ "Shutdown the server now or MINUTES minutes later." });
   lines += ({ "REASON is a message why the shutdown is needed." });
   lines += ({ "Note: there is no way to stop a shutdown." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tshutdown 5 were upgrading the server's memory." });
   lines += ({ "\tshutdown now sorry were experiencing major problems." });
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "check");
   add_also("wiz", "clean");
   add_also("wiz", "clone");
   add_also("wiz", "dest");
   add_also("wiz", "eval");
   add_also("wiz", "update");

   add_also("admin", "dumpstate");
   add_also("admin", "rebuild");
   add_also("admin", "warmboot");
}

void do_shutdown(void) {
   string *usrs;
   object *objs;
   int i, max, j, jmax;

   usrs = OBJECT_D->query_object_owners();
   max = sizeof(usrs);
   for (i = 0; i < max; i++) {
      objs = OBJECT_D->query_objects_by_owner(usrs[i]);
      jmax = sizeof(objs);
      for (j = 0; j < jmax; j++) {
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
      this_player()->more(usage());
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

static void main(string arg) {
   object *usrs;
   string time;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(arg, "%s %s", time, reason) != 2) {
      this_player()->more(usage());
      return;
   }

   if (lowercase(time) == "now") {
      LOG_D->write_log("shutdown", ctime(time()) + ": " +
         this_player()->query_Name() + " forced a shutdown.\n" + "REASON: " +
         reason + "\n");
      do_shutdown();
   } else {
      LOG_D->write_log("shutdown", ctime(time()) + ": " +
         this_player()->query_Name() + " forced a shutdown.\n" + "REASON: " +
         reason + "\n");
      countdown(str2val(time));
   }
}
