static int micro_beat_handle;
static int clean_up_handle;
static int save_game_handle;
static int heartbeat_counter;
static int micros_count;
static int seconds_count;
static int minutes_count;
static int hours_count;
static int days_count;
static int reset_counter;
static float micro_beat_interval;
static mapping timed_events, queued_events;

static void setup(void) {
   EVENT_D->add_event("micro_beat");
   EVENT_D->add_event("second_tick");
   EVENT_D->add_event("minute_tick");
   EVENT_D->add_event("hour_tick");
   EVENT_D->add_event("day_tick");
   EVENT_D->add_event("heart_beat");

   heartbeat_counter = 0;
   micros_count = 0;
   seconds_count = 0;
   minutes_count = 0;
   hours_count = 0;
   days_count = 0;
   reset_counter = 0;
   queued_events = ([ ]);
   timed_events = (["seconds" : ([ ]), "minutes" : ([ ]), "hours" : ([ ]), "days" : ([  ])]);
   micro_beat_interval = 1.0 / (float) MICROS_PER_SECOND;

   if (!micro_beat_handle) {
      micro_beat_handle = call_out("micro_beat", micro_beat_interval);
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

void dispatch_timed_events(string unit) {
   int i;
   int unit_count;
   
   unit_count = call_other(this_object(), "get_" + unit + "_count");
   if (timed_events[unit][unit_count]) {
      for (i = 0; i < sizeof(timed_events[unit][unit_count]); i++) {
         catch(call_other(timed_events[unit][unit_count][i][1],
            timed_events[unit][unit_count][i][0]) );
      }
   timed_events[unit][unit_count] = nil;
   }
}

static int get_seconds_count() {
   return seconds_count;
}

static int get_minutes_count() {
   return minutes_count;
}

static int get_hours_count() {
   return hours_count;
}

static int get_days_count() {
   return days_count;
}

static void heart_beat(void) {
   EVENT_D->event("heart_beat");
}

static void reset(void) {
   EVENT_D->event("reset");
}

static void day_tick(void) {
   days_count++;

   EVENT_D->event("day_tick");
   dispatch_timed_events("days");
}

static void hour_tick(void) {
   hours_count++;
   
   if (hours_count > 23) {
      hours_count = 0;
      day_tick();
   }
   EVENT_D->event("hour_tick");
   dispatch_timed_events("hours");
}

static void minute_tick(void) { /* approximation of 1 minute */
   minutes_count++;
   reset_counter++;

   if (minutes_count > 59) {
      minutes_count = 0;
      hour_tick();
   }

   if (reset_counter == RESET_INTERVAL) {
      reset_counter = 0;
      reset();
   }

   EVENT_D->event("minute_tick");
   dispatch_timed_events("minutes");
}

static void second_tick() { /* approximation of 1 second */
   int i;
   heartbeat_counter++;
   seconds_count++;

   if (heartbeat_counter >= HEART_BEAT_INTERVAL) {
      heartbeat_counter = 0;
      heart_beat();
   }
   if (seconds_count > 59) {
      seconds_count = 0;
      minute_tick();
   }
   EVENT_D->event("second_tick");
   dispatch_timed_events("seconds");
}

static void micro_beat() {
   micro_beat_handle = call_out("micro_beat", micro_beat_interval);
   micros_count++;
   if (micros_count >= MICROS_PER_SECOND) {
      micros_count = 0;
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

/* add_timed_event: calls a function after amount of time indicated in function 
 * arguments.  'amount' is the number of times the 'unit' passes by before
 * the function 'name' gets called inside of previous_object().  Valid intervals
 * are 'second', 'minute' and 'hour'. */
void add_timed_event(string unit, int amount, string name) {
   object ob;
   int unit_count;
   int max_size;

   ob = previous_object();
   if (amount < 1) {
      error("Arg 2 must be greater than 0.");
   }
   switch(unit) {
      case "seconds":
      case "minutes":
         max_size = 60;
         break;
      case "hours":
         max_size = 24;
         break;
      case "days":
         max_size = 999999999;
         break;
      default:
         error("Arg 1 must be a legal unit of time.");
         break;
   }
   unit_count = call_other(this_object(), "get_" + unit + "_count");
   if (amount < max_size) {
      if (unit_count + amount < max_size) {
         unit_count += amount;
      } else {
         unit_count = amount - (max_size - unit_count);
      } if (!timed_events[unit][unit_count]) {
         timed_events[unit][unit_count] = ({ ({name, ob}) });
      } else {
         timed_events[unit][unit_count] += ({ ({name, ob}) });
      }
   } else {
      error("Amount cannot exceed max unit size: Unit: " + unit +
         " Max_size: " + max_size);
   }
}

void create(void) {
   setup();
}

void upgraded(void) {
   setup();
}
