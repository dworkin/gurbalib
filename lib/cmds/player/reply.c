void main( string what ) {
  object usr;
  string who, where;

  who = this_player()->query_last_tell();

  if( !who || who == "" ) {
    write( "Nobody has told you anything lately." );
    return;
  }

  if ( !what || what == "" ) {
    write( "You will reply to " + capitalize(who) + "." );
    return;
  }

  if( sscanf( who, "%s@%s", who, where ) == 2 ) {
    /* intermud tell */
    IMUD_D->do_tell( who, where, what );
    write( "You tell %^PLAYER%^" + capitalize(who) + "@" + where + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n" );
  } else {
    usr = USER_D->find_player(who);
    if( usr && !usr->query_ignored(this_player()->query_name()) ) {
        usr->message( "%^PLAYER%^" + capitalize(this_player()->query_name()) + "%^RESET%^ tells you: %^TELL_FROM%^" + what + "%^RESET%^\n" );
        usr->set_last_tell( lowercase( this_player()->query_name() ) );
        write( "You tell%^PLAYER%^ " + capitalize(who) + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n" );
    } else {
        write( "You can't seem to reach " + who + ".\n" );
    }
  }
}
