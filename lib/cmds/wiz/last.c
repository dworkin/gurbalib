void usage() {
  write("Usage: last [-h] [player]\n");
  write("Find out when a player was last logged in.\n");
  write("If no player is given show last for everyone.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

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
