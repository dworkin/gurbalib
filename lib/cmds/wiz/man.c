/* A highly advanced help command 
 * Aphex
 * :)
 */

void main( string arg ) {
  string file;
  string *tmp;
  string *lines;
  int i;
  int where;

  if ( !arg || arg == "" ) {
    arg = "intro";
  }

  if( SECURE_D->query_wiz(this_player()->query_name()) != 1) {
    return;
  }

  arg = lowercase(arg);
  
  file = normalize_path( arg, "/doc/" );
  
  if( file_exists( file ) < 1 ) {
    file = normalize_path( arg, "/doc/afun/");
    if( file_exists(file) < 1 ) {
      file = normalize_path( arg, "/doc/kfun/");
      if(file_exists(file) < 1 ) {
        write( capitalize(arg) + ": Unknown man page." );
        write_file("/logs/man", capitalize(this_player()->query_name()) + " on " + ctime(time()) + ": " + arg + "\n");
        return;
      }
    }
  }
  
  tmp = explode( read_file( file ), "\n" );
  lines = ({ });
  write("Manpage for " + capitalize(arg) + ".\n");
  for( i = 0; i < strlen("Manpage for " + arg + "."); i++){
    out("-");
  }
  write("\n");
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
  
  
  this_player()->more( lines );
}
