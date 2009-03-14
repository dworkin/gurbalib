void write( string str ) {
  if( !this_user() )
    return;
  this_player()->message( str );
  if( this_player()->is_snooped() )
    this_player()->do_snoop( str );
}

