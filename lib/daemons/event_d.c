#include <status.h>

/* Uncomment this to debug the event Daemon */
/* #define DEBUG_EVENT_D 1 */

#ifdef DEBUG_EVENT_D
#define DB(X) console_msg("eventd: " + X + "\n")
#else
#define DB(X)
#endif

#define REMAINING_TICKS status()[ST_TICKS]

static mapping global_events;
int eventid;

void create(void) {
   global_events = ([]);
}

void add_event(string name) {
   if (!global_events) {
      global_events = ([]);
   }

   if (!global_events[name]) {
      global_events[name] = ([]);
   }
}

void remove_event(string name) {
   global_events[name] = nil;
}

void subscribe_event(string name) {
   global_events[name][previous_object()] = 1;
}

void unsubscribe_event(string name) {
   global_events[name][previous_object()] = nil;
}

/* set this_player for heartbeats coming from ob in player inv */
static void special_heart_beat(object ob, string func, varargs mixed args) {
   rlimits(MAX_DEPTH; MAX_TICKS) {
      set_this_player(ob->query_environment() );
      if (sizeof(args) > 0) {
         call_other(ob, func, args);
       } else {
         call_other(ob, func);
       }
   }
}

void dispatch_event(string name, object *obs, int *counters, int id,
   mixed *args) {
   int i, max_i, ticks_used, guard_handle;

   i = counters[0];
   max_i = counters[1];

   DB("dispatch: " + name + " (" + id + ") : starting at " + (i + 1) +
      " out of " + (max_i + 1));

   /* First see if there are any more objects after this one
      then dispatch for the next one to make sure all get the event
      in case of errors */
   if (i < max_i) {
      guard_handle = call_out("dispatch_event", 0, name, obs, counters,
         id, args);
   } else {
      guard_handle = 0;
   }

   rlimits(MAX_DEPTH; -1) {
      while ((ticks_used < (MAX_TICKS) / 50) && (i <= max_i)) {
         counters[0] = i + 1;

         rlimits(MAX_DEPTH; MAX_TICKS) {
            if (obs[i]) {
               if (name == "heart_beat" && obs[i]->query_environment() &&  
                obs[i]->query_environment()->is_player() ) {
                 call_out("special_heart_beat", 0, obs[i],           
                  "event_" + name, args);
               } else {
                  if (sizeof(args) > 0) {
                     call_other(obs[i], "event_" + name, args);
                  } else {
                     call_other(obs[i], "event_" + name);
                  }
               }
            }
            ticks_used += (MAX_TICKS - REMAINING_TICKS);
         }
         i++;
      }
   }
   if (guard_handle && (counters[0] > counters[1])) {
      DB("dispatch: " + name + " (" + id + ") : finished with " + (i) +
         " out of " + (max_i + 1) + " subscribers, removing guard call_out.");
      remove_call_out(guard_handle);
   } else {
      DB("dispatch: " + name + " (" + id + ") : suspending, next subscriber: " +
         (counters[0] + 1) + " out of " + (counters[1] + 1));
   }
}

void event(string name, varargs mixed args ...) {
   object *obs;
   int i;

   if (!global_events[name]) {
      return;
   }

   eventid++;

   obs = map_indices(global_events[name]);

   if (!obs || sizeof(obs) == 0) {
      return;
   }

   DB("event: " + name + " (" + eventid + "), " + sizeof(obs) +
      " subscribers.");
   dispatch_event(name, obs, ( { 0, sizeof(obs) - 1} ), eventid, args);
}

void upgraded(void) {
   eventid = 0;
}
