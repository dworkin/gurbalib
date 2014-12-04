static int micro_beat_handle;
static int clean_up_handle;
static int save_game_handle;
static int heartbeat_counter;
static int second_counter;
static int minute_counter;
static int hour_counter;
static int reset_counter;

static void setup(void) {
   EVENT_D->add_event("micro_beat");
   EVENT_D->add_event("second_tick");
   EVENT_D->add_event("minute_tick");
   EVENT_D->add_event("hour_tick");
   EVENT_D->add_event("heart_beat");

   heartbeat_counter = 0;
   second_counter = 0;
   minute_counter = 0;
   hour_counter = 0;
   reset_counter = 0;

   if (!micro_beat_handle) {
      micro_beat_handle = call_out("micro_beat", MICRO_BEAT_INTERVAL);
   }

   if (!WORLD_PERSIST) {
      EVENT_D->add_event("clean_up");

      if (!clean_up_handle) {
	 clean_up_handle = call_out("clean_up", CLEAN_UP_INTERVAL);
      }

      EVENT_D->add_event("reset");
   }

#ifdef SYS_PERSIST
   if (!save_game_handle) {
      save_game_handle = call_out("save_game", DUMP_INTERVAL);
   }
#endif
}

static void heart_beat(void) {
   EVENT_D->event("heart_beat");
}

static void reset(void) {
   EVENT_D->event("reset");
}

static void hour_tick(void) {
   EVENT_D->event("hour_tick");
}

static void minute_tick(void) { /* approximation of 1 minute */
   hour_counter++;
   reset_counter++;

   if(hour_counter > 59) {
      hour_counter = 0;
      hour_tick();
   }

   if(reset_counter == RESET_INTERVAL) {
      reset_counter = 0;
      reset();
   }

   EVENT_D->event("minute_tick");
}

static void second_tick() { /* approximation of 1 second */
   heartbeat_counter++;
   minute_counter++;

   if(heartbeat_counter > 1) {
      heartbeat_counter = 0;
      heart_beat();
   }

   if(minute_counter > 59) {
      minute_counter = 0;
      minute_tick();
   }
      
   EVENT_D->event("second_tick");
}

static void micro_beat() {
   micro_beat_handle = call_out("micro_beat", MICRO_BEAT_INTERVAL);
   second_counter++;
/* TODO: Make this so seconds_counter calculates the number of microbeats
     before a second is reached based on MICRO_BEAT_INTERVAL.  Hardcoded 
     for now. */
   if(second_counter > 4) {
      second_counter = 0;
      second_tick();
   }

   EVENT_D->event("micro_beat");
}

static void clean_up(void) {
   clean_up_handle = 0;

   if (!WORLD_PERSIST) {
      clean_up_handle = call_out("clean_up", CLEAN_UP_INTERVAL);
      EVENT_D->event("clean_up");
   }
}

static void save_game(void) {
#ifdef SYS_PERSIST
   save_game_handle = call_out("save_game", DUMP_INTERVAL);
   DRIVER->save_game();
#else
   save_game_handle = 0;
#endif
}

void create(void) {
   setup();
}

void upgraded(void) {
   setup();
}
