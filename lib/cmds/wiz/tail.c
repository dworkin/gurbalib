void usage() {
  write("Usage: tail [-h] [file]\n");
  write("Show the tail end of a file " +
    "(print it to the screen).\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: more, cat, browse\n");
}

void main( string arg ) {
   string file;
   string *tmp;
   string *lines;
   int i;
   int where;
   int num_lines, start;

   if( !arg || arg == "" ) {
      arg = this_environment()->file_name();
   }
   if (sscanf(str, "-%s",str)) {
     usage();
     return;
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
  
   num_lines = sizeof( lines );
   start = num_lines - 20;
   if( start < 0 ) {
      start = 0;
   }
   for( i = start; i < num_lines; i++ ) {
      write(lines[i]);
   }
}
