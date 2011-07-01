void usage() {
  write("Usage: rmemote [-h] NAME\n");
  write("Remove an emote from the emote database.\n");

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

  if( EMOTE_D->is_emote(str) ) {
    EMOTE_D->remove_emote( str );
    write( "Emote removed.\n" );
  } else {
    write( "No such emote.\n" );
  }
}
