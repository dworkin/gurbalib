/* 
   Module providing autonomous movement for monsters.
   Implementation by Cerihan - 3/14/09
*/

#ifndef MAX_WANDER
#define MAX_WANDER 20
#endif

int movement_mintime;
int movement_maxtime;
string wander_area;
int wander_enable;
int next_move;
int wander_count;

void set_wander_area(string area) {
   wander_area = area;
}

void start_wander(int mintime, int maxtime) {
   movement_mintime = mintime;
   movement_maxtime = maxtime;

   if (mintime < 1) {
      movement_mintime = 1;
   }
   if (maxtime < 1) {
      movement_maxtime = 1;
   }
   if (maxtime < mintime) {
      movement_maxtime = mintime;
   }

   /* start the call_out loop */
   wander_enable = 1;
   next_move = time() + random(movement_maxtime - movement_mintime) + 
      movement_mintime;
}

void stop_wander(void) {
   wander_enable = 0;
}

void wander(void) {
   mixed *exits;
   int i;

   /*
    * It is quite normal that the 'master/blueprint' doesn't have an 
    * environment.  However, this should never happen with a clone. 
    * Hence, error if this is a clone, ignore otherwise.
    */
   if (!this_object()->query_environment()) {
      if (clone_num() != 0) {
         error("Wandering clone without environment");
      } else {
         return;
      }
   }

   if (wander_count++ < MAX_WANDER) {
      /* Go ahead and set up the next call_out */
      next_move = time() + random(movement_maxtime - movement_mintime) +
         movement_mintime;
   } else {
      stop_wander();
      return;
   }

   /* Get a list of exits */
   exits = map_indices(this_object()->query_environment()->query_exits());

   /* try 3 times to find an exit that falls within our wander area. */
   for (i = 0; i < 3; i++) {
      string exit;
      object exarea;
      exit = random_element(exits);
      exarea = this_object()->query_environment()->query_exit_room(exit);
      if (exarea && exit) {
         if (!wander_area || exarea->query_in_area(wander_area)) {
            this_object()->query_environment()->unsubscribe_event("body_enter");
            this_object()->query_environment()->body_exit(this_object(), exit);
            this_object()->query_environment()->subscribe_event("body_enter");
            return;      /* success */
         }
      } else if (!exit) {
         /* No exits - no need to keep wandering. */
         stop_wander();
         return;
      }
   }
}

int no_cleanup(void) {
   return wander_enable != 0;
}

void event_body_enter(mixed * what) {

   if (what && objectp(what[0]) && what[0]->is_player()) {
      wander_count = 0;
      if (!wander_enable && movement_mintime) {
         start_wander(movement_mintime, movement_maxtime);
      }
   }
}

static void event_wander(void) {
   if (wander_enable && (time() >= next_move)) {
      wander();
   }
}
