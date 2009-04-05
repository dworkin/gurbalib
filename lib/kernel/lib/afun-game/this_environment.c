object this_environment( void ) {
  return( this_player() ? this_player()->query_environment() : nil );
}

