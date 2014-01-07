#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("bell");
   set_adj("small");
   set_short("A small bell");
   set_long("Your average small bell, however it's floating in the air, " +
      "next to the entrance.");
   set_gettable(0);
}

void post_move() {
   object room;

   room = query_environment();
   if (room) {
      query_environment()->subscribe_event("body_enter");
      query_environment()->subscribe_event("body_leave");
   }
   
}

void destruct(void) {
   object room;

   room = query_environment();
   if (room) {
      query_environment()->unsubscribe_event("body_enter");
      query_environment()->unsubscribe_event("body_leave");
   }
   ::destruct();
}

void event_body_enter(mixed * who) {
   query_environment()->tell_room(nil, "The small bell goes *DING*.\n");
}

void event_body_leave(mixed * who) {
   query_environment()->tell_room(nil, "The small bell goes *DONG*.\n");
}
