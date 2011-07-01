void usage() {
  write("Usage: mkwiz [-h] PLAYER\n");
  write("Make the player PLAYER a wizard.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: mkadmin\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    write( "Useage: mkwiz <name>\n" );
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( require_priv( "system" ) ) {
    SECURE_D->make_wizard( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
