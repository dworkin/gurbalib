mixed *query_verb_info( void ) {
  return( ({ "" }) );
}

mixed can_listen( void ) {
  return( 1 );
}

mixed do_listen( void ) {
  if( !this_environment()->do_listen( this_player() ) )
    write( "You hear nothing special." );
}
