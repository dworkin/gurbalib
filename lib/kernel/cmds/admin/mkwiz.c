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

  if (!USER_D->user_exists(str)) {
     write( "No such user: " + str + "\n" );
     return;
  }
  if (this_player()->query_name() == str) {
     write("You can not make yourself a wizard.\n");
     return;
  }

  if( !require_priv( "system" ) ) {
    write( "You need admin privileges to make wizards.\n" );
    return;
  }
    SECURE_D->make_wizard( str );
}
