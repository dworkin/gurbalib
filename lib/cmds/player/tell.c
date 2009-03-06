 void main( string who ) {
  object *usr;
  int i;
  int flag;
  string what;
  string where;

  if(sscanf(who, "\"%s\" %s", who, what) != 2) {
    sscanf( who, "%s %s", who, what );
  }

  if( sscanf( who, "%s@%s", who, where) == 2 ) {
    /* intermud tell */
    IMUD_D->do_tell( who, where, what );
    write( "You tell " + capitalize(lowercase(who)) + "@" + where + ": " + what + "\n" );
  } else {
    usr = users();
    for( i = 0; i < sizeof( usr ); i++ ) {
      if( usr[i]->query_name() == lowercase(who) ) {
	usr[i]->query_player()->message( capitalize(this_player()->query_name()) + " tells you: " + what + "\n" );
	usr[i]->query_player()->set_last_tell( lowercase( this_player()->query_name() ) );
	write( "You tell " + capitalize(lowercase(who)) + ": " + what + "\n" );
	flag = 1;
      }
    }
    
    if( !flag ) {
      write( "You can't seem to reach " + lowercase(who) + ".\n" );
    }
  }
}
