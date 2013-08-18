/* Read in the default objects that are loaded at boot */

/* Returns a default init list. */
private string *get_default_objects() {
   string *objects;

   objects = ( { SCHEDULE_D, TIME_D, USER_D } );

#ifdef SYS_NETWORKING
   objects += ( {
       TELNET_D,
#ifndef DISABLE_FTP
        FTP_D,
#endif
#ifndef DISABLE_IMUD
	IMUD_D,
#endif
   } );
#endif

   objects += ( {
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
      PARSE_D, 
      STARTING_ROOM
   } );
   return objects;
}

static void create() {
   string *objects;
   int count;
   int size;

   objects = get_default_objects();

   if (!objects) {
      return;
   }

   rlimits(MAX_DEPTH; -1) {
      for (count = 0, size = sizeof(objects); count < size; count++) {
	 object ob;

	 if (!(ob = find_object(objects[count]))) {
	    rlimits(MAX_DEPTH; MAX_TICKS) {
	       call_other(objects[count], "???");
	    }
	 }
      }
   }
}
