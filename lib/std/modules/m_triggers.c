static mapping patterns;

void respond( string message );

void add_pattern( string pattern, string action ) {
  
  if( !patterns ) {
    patterns = ([ ]);
  }
  patterns[pattern] = action;
}

void outside_message( string msg ) {
  string *pats;
  string left;
  string right;
  int i,j;
  int args;

  left = "";
  right = "";

  if( msg[strlen( msg )-1] == '\n' )
    msg = msg[..strlen( msg ) -2 ];


  msg = ANSI_D->strip_colors( msg );

  if( !patterns )
    patterns = ([ ]);

  pats = map_indices( patterns );
  for( i = 0; i < sizeof( pats ); i++ ) {
    args = 0;
    for( j = 0; j < strlen( pats[i] ); j++ ) {
      if( pats[i][j] == '%' )
	args++;
    }
    if( args == 0 ) {
      if( strstr( msg, pats[i] ) != -1 ) {
	respond( patterns[pats[i]] );
	return;
      }
    } else if( sscanf( msg, pats[i], left, right ) == args ) {
      /* We found a match */
      msg = patterns[pats[i]];
      msg = replace_string( msg, "$1", left );
      msg = replace_string( msg, "$2", right );
      respond( msg );
      return;
    }
  }
}
