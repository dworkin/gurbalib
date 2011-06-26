void usage() {
  write("Usage: reply [-h] MSG\n");
  write("Reply with message MSG to the last person that sent a tell to you.\n");
  write("It's dangerous to rely on this command, lots of times someone will\n");
  write("send you a tell just as your sending your MSG and it will goto " +
    "someone else.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object usr;
  string who, where;

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  who = this_player()->query_last_tell();

  if( !who || who == "" ) {
    write( "Nobody has told you anything lately." );
    return;
  }

  if( sscanf( who, "%s@%s", who, where ) == 2 ) {
    /* intermud tell */
    IMUD_D->do_tell( who, where, str );
    write( "You tell %^PLAYER%^" + capitalize(who) + "@" + where + 
      "%^RESET%^: %^TELL_TO%^" + str + "%^RESET%^\n" );
  } else {
    usr = USER_D->find_player(who);
    if( usr && !usr->query_ignored(this_player()->query_name()) ) {
        usr->message( "%^PLAYER%^" + capitalize(this_player()->query_name()) + 
          "%^RESET%^ tells you: %^TELL_FROM%^" + str + "%^RESET%^\n" );
        usr->set_last_tell( lowercase( this_player()->query_name() ) );
        write( "You tell%^PLAYER%^ " + capitalize(who) + 
          "%^RESET%^: %^TELL_TO%^" + str + "%^RESET%^\n" );
    } else {
        write( "You can't seem to reach " + who + ".\n" );
    }
  }
}
