void main( string str ) {
  if( str == "" ) {
    write( "Usage: rwho mudname\n" );
    return;
  }

  IMUD_D->do_who( str );
}
