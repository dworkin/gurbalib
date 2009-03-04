/* A highly advanced more command 
 * Fudge
 */

void main( string arg ) {
  string file;
  string *tmp;
  string *lines;
  int i;
  int where;

  if( arg == "" ) {
    arg = this_environment()->file_name();
  }

  file = normalize_path( arg, this_player()->query_env( "cwd" ) );

  if( file_exists( file ) < 1 ) {
    write( arg + ": File not found." );
    return;
  }

  tmp = explode( read_file( file ), "\n" );
  lines = ({ });
  for( i = 0; i < sizeof( tmp ); i++ ) {
    if( strlen( tmp[i] ) > 79 ) {
      /* Big line. Break it up. */
      where = 0;
      while( where < strlen( tmp[i] ) ) {
	if( where + 79 < strlen( tmp[i] ) ) {
	  lines += ({ tmp[i][where..where+78] });
	  where += 79;
	} else {
	  lines += ({ tmp[i][where..] });
	  where = strlen(tmp[i]);
	}
      }
    } else {
      lines += ({ tmp[i] }) ;
    }
  }
  

  this_player()->more( lines, 0 );
}
