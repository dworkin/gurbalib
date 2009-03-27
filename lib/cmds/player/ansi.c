void main( string str ) {
  if( str == "on" || str == "On" || str == "1" ) {
    this_player()->set_ansi( 1 );
    out( "Turning on ANSI.\n" );
  } else if( str == "off" || str == "Off" || str == "0" ) {
    this_player()->set_ansi( 0 );
    out( "Turning off ANSI.\n" );
  } else if( str == "show" || str == "display" ) {
    out( ANSI_D->color_table() );
  } else {
    out( "Usage:\nansi <on/off/show>\n\nTurns on or off ANSI support.\nAlso can display the set of colours.\n" );
  }
}

