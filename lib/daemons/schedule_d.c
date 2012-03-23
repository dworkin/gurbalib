static int heart_beat_handle;
static int clean_up_handle;
static int reset_handle;
static int save_game_handle;

static void setup() {
   EVENT_D->add_event("heart_beat");

   if (!heart_beat_handle) {
      heart_beat_handle = call_out("heart_beat", 2);
   }

   if (!WORLD_PERSIST) {
      EVENT_D->add_event("clean_up");

      if (!clean_up_handle) {
	 clean_up_handle = call_out("clean_up", CLEAN_UP_INTERVAL);
      }

      EVENT_D->add_event("reset");

      if (!reset_handle) {
	 reset_handle = call_out("reset", RESET_INTERVAL);
      }
   }

#ifdef SYS_PERSIST
   if (!save_game_handle) {
      save_game_handle = call_out("save_game", DUMP_INTERVAL);
   }
#endif
}

static void heart_beat() {
   heart_beat_handle = call_out("heart_beat", HEART_BEAT_INTERVAL);
   EVENT_D->event("heart_beat");
}

static void clean_up() {
   clean_up_handle = 0;

   if (!WORLD_PERSIST) {
      clean_up_handle = call_out("clean_up", CLEAN_UP_INTERVAL);
      EVENT_D->event("clean_up");
   }
}

static void reset() {
   reset_handle = 0;
   if (!WORLD_PERSIST) {
      reset_handle =
	 call_out("reset", (RESET_INTERVAL / 2) + random(RESET_INTERVAL));
      EVENT_D->event("reset");
   }
}

static void save_game() {
#ifdef SYS_PERSIST
   save_game_handle = call_out("save_game", DUMP_INTERVAL);
   DRIVER->save_game();
#else
   save_game_handle = 0;
#endif
}

void create() {
   setup();
}

void upgraded() {
   setup();
}
