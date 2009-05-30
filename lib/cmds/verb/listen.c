string *query_verb_info() {
  return( ({ "" }) );
}

int can_listen() {
  return( 1 );
}

void do_listen() {
  if( !this_environment()->do_listen( this_player() ) )
    write( "You hear nothing special." );
}
