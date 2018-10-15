/* Read in the default objects that are loaded at boot */

/* Returns a default init list. */
private string *get_default_objects(void) {
   string *objects;

   objects = ( { EVENT_D, SCHEDULE_D, TIME_D, USER_D } );

   objects += ({

#ifdef SYS_NETWORKING
      TELNET_D,
#ifndef DISABLE_FTP
      FTP_D,
#endif
#endif

#ifndef DISABLE_IMUD
      IMUD_D,
#endif
   });

   objects += ({
      COMMAND_D,
      CHANNEL_D,
      OBJECT_D,
      SKILL_D,
      RACE_D,
      ANSI_D,
      MONEY_D,
      BANISH_D, 
      SITEBAN_D, 
      GUILD_D, 
      LANGUAGE_D, 
      EMOTE_D,
      PARSE_D, 
      QUEST_D,
      LINKDEAD_D,
      STARTING_ROOM
   });

   return objects;
}

static void create(void) {
   string *objects;
   int count, size;

   objects = get_default_objects();

   if (!objects) {
      return;
   }

   if (file_exists("/data") == 0) {
      console_msg("Setting up directories\n");

      make_dir("/data");
      make_dir("/data/banished");
      make_dir("/data/banned");
      make_dir("/data/banned/a");
      make_dir("/data/banned/b");
      make_dir("/data/banned/c");
      make_dir("/data/fortunes");
      make_dir("/data/mail");
      make_dir("/data/messages");
      make_dir("/data/players");

      if (file_exists("/sys/daemons/data") == 0) {
         make_dir("/sys/daemons/data");
         make_dir("/sys/daemons/data/users");
      }

      if (file_exists("/daemons/data") == 0) {
         make_dir("/daemons/data");
      }

      if (file_exists("/domains/players") == 0) {
         make_dir("/domains/players");
      }

      if (file_exists("/kernel/daemons/data") == 0) {
         make_dir("/kernel/daemons/data");
      }

      if (file_exists("/logs") == 0) {
         make_dir("/logs");
         make_dir("/logs/errors");
         make_dir("/logs/errors/runtime");
         make_dir("/logs/nobody");
      }

      if (file_exists("/tmp") == 0) {
         make_dir("/tmp");
      }

      if (file_exists("/wiz") == 0) {
         make_dir("/wiz");
      }
   }

   console_msg("Setting up events\n");
   EVENT_D->add_event("player_login");
   EVENT_D->add_event("player_logout");
   EVENT_D->add_event("player_linkdeath");
   EVENT_D->add_event("player_unlinkdeath");
   EVENT_D->add_event("new_player");

   console_msg("Loading daemons\n");
   rlimits(MAX_DEPTH; -1) {
      for (count = 0, size = sizeof(objects); count < size; count++) {
         object ob;

         if (!(ob = find_object(objects[count]))) {
            rlimits(MAX_DEPTH; MAX_TICKS) {
               console_msg("init: loading " + objects[count] + "\n");
               call_other(objects[count], "???");
            }
         }
      }
   }
   DRIVER->init_done();
}

int file_is_daemon(string str) {
   int x, max;
   string *dirs;

   dirs = ({"/daemons/"});
   dirs += ({"/sys/daemons/"});

   max = sizeof(dirs);
   for (x = 0; x < max; x++) {
      if (strstr(str, dirs[x]) == 0) {
         return 1;
      }
   }

   return 0;
}
