inherit M_BOARD;

void setup( void ) {
  set_id( "board" );
  set_adj( "message", "large" );
  set_long( "" );
  set_in_room_desc( "A huge message board." );
  set_board_id( "fighter" );
  query_environment()->subscribe_event( "body_look" );
  query_environment()->subscribe_event( "body_look_at" );
}

void destruct( void ) {
  query_environment()->unsubscribe_event( "body_look" );
  query_environment()->unsubscribe_event( "body_look_at" );
  ::destruct();
}

void event_body_look( mixed *who) {
  set_in_room_desc( "The Fighters board of discussion [" + query_message_count() + " msgs, " + query_new_message_count() + " new]" );
}

void event_body_look_at( mixed *who) {
  if( lowercase(who[1]->query_id()) == "board" ) {
    set_long( query_message_list( who[0]->query_name() ) );
  }
}
