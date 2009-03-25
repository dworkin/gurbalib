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
    write( "You tell " + capitalize(who) + "@" + where + ": " + what + "\n" );
  } else {
    who = lowercase(who);
    usr = USER_D->find_player(who);
    if( usr && !usr->query_ignored(this_player()->query_name()) ) {
      usr->message( capitalize(this_player()->query_name()) + " tells you: " + what + "\n" );
      usr->set_last_tell( lowercase( this_player()->query_name() ) );
      write( "You tell " + capitalize(who) + ": " + what + "\n" );
    } else {
      write( "You can't seem to reach " + who + ".\n" );
    }
  }
}
