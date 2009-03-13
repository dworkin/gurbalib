void main( string str ) {
  if( !str || str == "" ) {
    /* Not starting with a file */
    this_player()->edit("");
    this_player()->edit( "file" );
  } else {
    this_player()->write( "Starting editor..." );
    this_player()->edit( "e " + str );
    this_player()->edit( "file" );
  }
}
