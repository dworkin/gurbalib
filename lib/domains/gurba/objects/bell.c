inherit OBJECT;

void setup(void) {
   set_id("bell");
   set_adj("small");
   set_long("Your average small bell.");
   set_in_room_desc("A small bell is floating in the air next to the " +
      "entrance.");
   set_gettable(0);
   query_environment()->subscribe_event("body_enter");
   query_environment()->subscribe_event("body_leave");
}

void destruct(void) {
   query_environment()->unsubscribe_event("body_enter");
   query_environment()->unsubscribe_event("body_leave");
   ::destruct();
}

void event_body_enter(mixed * who) {
   query_environment()->tell_room(nil, "The small bell goes *DING*.\n");
}

void event_body_leave(mixed * who) {
   query_environment()->tell_room(nil, "The small bell goes *DONG*.\n");
}
