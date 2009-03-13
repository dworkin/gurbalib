void main( string str ) {
  if( !str || str == "" ) {
    write( "Usage: locate player-name\n" );
    return;
  }

  IMUD_D->do_locate( str );
}
