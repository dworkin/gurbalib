void main( string who ) {
  object usr;
  string what, where;

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
    write( "You tell %^PLAYER%^" + capitalize(who) + "@" + where + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n" );
  } else {
    who = lowercase(who);
    usr = USER_D->find_player(who);
    if( usr && (!usr->query_ignored(this_player()->query_name()) || query_wizard(this_player())) ) {
      usr->message( "%^PLAYER%^"+ capitalize(this_player()->query_name()) + "%^RESET%^%^TELL_FROM%^ tells you: " + what + "%^RESET%^\n" );
      usr->set_last_tell( lowercase( this_player()->query_name() ) );
      write( "You tell " + "%^PLAYER%^" + capitalize(who) + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n" );
    } else {
      write( "You can't seem to reach " + who + ".\n" );
    }
  }
}
