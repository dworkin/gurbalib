void usage() {
  write("Usage: mkwizdir [-h] PLAYER\n");
  write("Make the homedirectory for wizard PLAYER.\n");
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
    SECURE_D->create_homedir( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
