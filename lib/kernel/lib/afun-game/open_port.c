static void open_port( mixed args... ) {
  if( !require_priv( "system" ) ) {
    error( "Illegal call to open_port" );
  }

  ::open_port( args... );
}
