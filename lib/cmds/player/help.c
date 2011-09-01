void usage() {}  // This is a dumy function...
		// instead edit /docs/help/help

void show_file(string filename) {
  string *tmp;
  string *lines;
  int i, len, where;
  mixed width;

  width = this_player()->query_env("width");
  if(!intp(width) || width < 2) width = DEFAULT_WIDTH;

  tmp = explode( read_file( filename ), "\n" );
  lines = ({ });
  write("Help for " + capitalize(filename) + ".\n");
  for( i = 0; i < strlen("Help for " + filename + "."); i++){
    out("-");
  }
  write("\n");
  for( i = 0; i < sizeof( tmp ); i++ ) {
    if( strlen( tmp[i] ) > width ) {
      /* Big line. Break it up. */
      where = 0;
      len = strlen( tmp[i]);
      while( where < len ) {
	if( where + width < len ) {
	  lines += ({ tmp[i][where..(where+width-1)] });
	  where += width;
	} else {
	  lines += ({ tmp[i][where..] });
	  where = len;
	}
      }
    } else {
      lines += ({ tmp[i] });
    }
  }
  
  this_player()->more( lines );
}

void main( string arg ) {
  string file;
  if ( !arg || arg == "" ) {
    arg = "help";
  }

  if (sscanf(arg, "-%s",arg)) {
     arg = "help";
  }

  arg = lowercase(arg);
  
  file = normalize_path( arg, "/doc/help/" );
  
  if( file_exists( file ) < 1 ) {
    if( query_wizard( this_player() ) ) {
      file = normalize_path( arg, "/doc/help/wiz/");
      if( file_exists(file) < 1 ) {
	write( capitalize(arg) + ": Unknown help topic." );
	LOG_D->write_log("help", capitalize(this_player()->query_name()) + 
           " on " + ctime(time()) + ": " + arg + "\n");
	return;
      }
    } else {
      write( capitalize(arg) + ": Unknown help topic." );
      write_file("/logs/help", capitalize(this_player()->query_name()) + 
         " on " + ctime(time()) + ": " + arg + "\n");
      return;
    }
  }

  show_file(file);
}
