/* Read in the default objects that are loaded at boot */

/* Returns a default init list. */
private string *get_default_objects() {
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
   } );

   objects += ( {
      COMMAND_D,
      CHANNEL_D,
      OBJECT_D,
      RACE_D,
      ANSI_D,
      SKILL_D,
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
   } );

   return objects;
}

static void create() {
   string *objects;
   int count, size;

   objects = get_default_objects();

   if (!objects) {
      return;
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
