void main( string str ) {
  string msg;

  if( !require_priv( "system" ) ) {
    write( "Access denied" );
    return;
  }

  if( str != "" ) {
    msg = LAST_D->query_entry( lowercase( str ) );
  } else {
    msg = LAST_D->query_list();
  }
  write( msg );
}
