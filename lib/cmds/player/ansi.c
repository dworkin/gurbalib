void usage() {
  write("Usage: ansi[-h] [on|off|show]\n");
  write("Used to turn on or off color support and show the settings.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\ton\tTurn on ANSI support.\n");
  write("\toff\tTurn off ANSI support.\n");
  write("\tshow\tDisplay your current ANSI support settings.\n");
}

// XXX Merge with color command....

void main( string str ) {
  if( str == "on" || str == "On" || str == "1" ) {
    this_player()->set_ansi( 1 );
    out( "Turning on ANSI.\n" );
  } else if( str == "off" || str == "Off" || str == "0" ) {
    this_player()->set_ansi( 0 );
    out( "Turning off ANSI.\n" );
  } else if( str == "show" || str == "display" ) {

// XXX make it so show displayes your current ansi status off, on...

    out( ANSI_D->color_table() );
  } else {
    usage();
  }
}

