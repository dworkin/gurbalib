void main( string str ) {
  string msg;

  if( str != "" ) {
    msg = LAST_D->query_entry( lowercase( str ) );
  } else {
    msg = LAST_D->query_list();
  }
  write( msg );
}
