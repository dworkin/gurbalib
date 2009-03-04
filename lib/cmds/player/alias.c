void main( string str ) {
  mapping alias;
  string *aliases;
  string cmd;
  string arg;
  int i;

  if( !str || str == "" ) {
    alias = this_player()->query_aliases();
    aliases = map_indices( alias );
    if( sizeof( aliases ) == 0 ) {
      write( "You have no aliases." );
      return;
    }

    write( "You have defined these aliases: " );
    for( i = 0; i < sizeof( aliases ); i++ ) {
      write( "  " + aliases[i] + "='" + alias[aliases[i]] + "'" );
    }
  } else {
    if( sscanf( str, "%s %s", cmd, arg ) != 2 ) {
      if( this_player()->is_alias( str ) ) {
	/* Remove an alias */
	write( "Alias '" + str + "' (" + this_player()->query_alias( str ) + ") removed." );
	this_player()->remove_alias( str );
	return;
      }

      write( "Usage: alias <cmds> <alias>" );
      return;
    }

    this_player()->add_alias( cmd, arg );
    write( "Alias '" + cmd + "' (" + arg + ") added." );
  }
}
