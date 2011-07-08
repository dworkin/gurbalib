void usage() {
  write("Usage: mkwizdir [-h] PLAYER\n");
  write("Make the home directory for wizard PLAYER.\n");
  write("By default you do not need to use this command, it gets done " +
    "automatically.\n");
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
    write( "You need admin privileges to make wizards.\n" );
  } 
}
