void usage() {
  write("Usage: tell [-h] WHO WHAT\n");
  write("Send a message WHAT to WHO.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  if (query_wizard( this_player() )) {
     write("See also: say ssay emote whisper\n");
  } else {
     write("See also: say emote whisper\n");
  }
}

void main( string who ) {
  object usr;
  string what, where;

  if (!who || who == "") {
     usage();
     return;
  }

  if (sscanf(who, "-%s",who)) {
     usage();
     return;
  }

  if(sscanf(who, "\"%s\" %s", who, what) != 2) {
    sscanf( who, "%s %s", who, what );
  }

  
  if(!what || what == "") {
    write("Tell " + who + " what?\n");
    return;
  }
  
  if( sscanf( who, "%s@%s", who, where) == 2 ) {
    /* intermud tell */
    IMUD_D->do_tell( who, where, what );
    this_player()->message( "You tell %^PLAYER%^" + capitalize(who) + "@" +
	     where + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n", 1 );
  } else {
    who = lowercase(who);
    usr = USER_D->find_player(who);
    if( usr && (!usr->query_ignored(this_player()->query_name()) || query_wizard(this_player())) ) {
      usr->message( "%^PLAYER%^"+ capitalize(this_player()->query_name()) +
	       "%^RESET%^%^TELL_FROM%^ tells you: " + what + "%^RESET%^\n", 1 );
      usr->set_last_tell( lowercase( this_player()->query_name() ) );
      this_player()->message( "You tell " + "%^PLAYER%^" + capitalize(who) +
	       "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n", 1 );
    } else {
      write( "You can't seem to reach " + who + ".\n" );
    }
  }
}
