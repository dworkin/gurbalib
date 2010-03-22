void main( string str ) {
  if( str ) {
    str = replace_string( str, "$N", this_player()->query_proper_name() );
  }

  this_player()->set_long( str );
  this_player()->simple_action( "$N $vchange $p looks." );
}
