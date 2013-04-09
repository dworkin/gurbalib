inherit "/std/modules/m_board";

void setup(void) {
   set_id("board");
   set_adj("message", "large");
   set_long("");
   set_short("A huge message board");
   set_board_id("bug");
   query_environment()->subscribe_event("body_look");
   query_environment()->subscribe_event("body_look_at");
}

void destruct(void) {
   query_environment()->unsubscribe_event("body_look");
   query_environment()->unsubscribe_event("body_look_at");
   ::destruct();
}

void event_body_look(mixed * who) {
   set_short("The infamous bug board [" + query_message_count() +
      " msgs, " + query_new_message_count() + " new]");
}

void event_body_look_at(mixed * who) {
   if (lowercase(who[1]->query_id()) == "board") {
      set_long(query_message_list(who[0]->query_name()) + 
         "Commands: post, read #, delete num\n");
   }
}
