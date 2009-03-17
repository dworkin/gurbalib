/* A highly advanced help command 
 * Aphex
 * :)
 */

void main( string arg ) {
  string file;
  string *tmp;
  string *lines;
  string header;
  int i;
  int where;

  if ( !arg ) {
    arg = "";
  }

  if( SECURE_D->query_wiz(this_player()->query_name()) != 1) {
    return;
  }

  arg = lowercase(arg);
  
  file = normalize_path( arg, "/doc/" );
  
  if( file_exists( file ) == 0 ) {
    file = normalize_path( arg, "/doc/afun/");
    if( file_exists(file) == 0 ) {
      file = normalize_path( arg, "/doc/kfun/");
      if(file_exists(file) == 0 ) {
        write( capitalize(arg) + ": Unknown man page." );
        write_file("/logs/man", capitalize(this_player()->query_name()) + " on " + ctime(time()) + ": " + arg + "\n");
        return;
      }
    }
  }
  
  if(file_exists(file) > 0) {
    header = "Manpage for "+arg+".";
    tmp = explode( read_file( file ), "\n" );
  } else {
    string * stuff;
    int j;

    header = "Index for "+arg+".";
    tmp = ({ });
    stuff = get_dir(file+"/*")[0];
    stuff -= ({ ".svn" });
    for(j=0;j<sizeof(stuff);j += 4) {
      string l;
      l = "";
      for(i=0;i<4;i++) {
        if(j+i < sizeof(stuff)) l += (stuff[j+i]+"                          ")[0..18];
      }
      tmp += ({ l });
    }
  }

  lines = ({ });
  write(header + "\n");
  for( i = 0; i < strlen(header); i++){
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
