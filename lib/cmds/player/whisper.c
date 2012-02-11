void usage() {
  write("Usage: whisper [-h] WHO MSG\n");
  write("Whisper a message MSG to WHO\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  if (query_wizard( this_player() )) {
     write("See also: tell say ssay emote\n");
  } else {
     write("See also: tell say emote\n");
  }
}

void main( string who) {
  object *usr;
  int i;
  int flag;
  string what;

  if ( !who || who == "" ) {
    usage();
    return;
  }
  if (sscanf(who, "-%s",who)) {
     usage();
     return;
  }
  
  sscanf(who, "%s %s", who, what);
  
  if (what && what != "") {
     what = capitalize(what);
  }

  usr = USER_D->query_players();
  flag = 0;
    for ( i = 0; i < sizeof (usr); i++) {
      if ((usr[i]->query_environment() == this_environment()) && 
        (usr[i]->query_name() == who)) {
	usr[i]->message( capitalize(this_player()->query_name()) + 
           " whispers to you: " + what + "\n");
	write( "You whisper to " + capitalize(who) + ": " + what + "\n");
	this_player()->query_environment()->tell_room(this_player(), 
          capitalize(this_player()->query_name()) + 
          " whispers something to " + capitalize(who) + ".\n", usr[i]);
	flag = 1;
      }
    }
  if (!flag) {
    write("Who did you want to whisper to?\n");
  }
}

