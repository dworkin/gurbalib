void usage() {
  write("Usage: mkadmin [-h] PLAYER\n");
  write("Make the player PLAYER an admin.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    usage();
    return;
  }
  
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( require_priv( "system" ) ) {
    SECURE_D->make_admin( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
