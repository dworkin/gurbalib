void usage() {
  write("Usage: mkadmin [-h] PLAYER\n");
  write("Make the player PLAYER an admin.\n");
  write("If you make someone an admin they are also considered a wizard.\n");
  write("If you run mkwiz on an admin it will demote them to a wizard.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: mkwiz\n");
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

  if (!USER_D->user_exists(str)) {
     write( "No such user: " + str + ".\n" );
     return;
  }

  if (this_player()->query_name() == str) {
     write("You can not make yourself an admin.\n");
     return;
  }

  if( !require_priv( "system" ) ) {
     write( "You need admin priveleges to make an admin.\n" );
     return;
  } 
  SECURE_D->make_admin( str );
}
