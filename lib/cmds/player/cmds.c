int col;

void usage() {
  write("Usage: cmds [-h] [-v]\n");
  write("cmds lists the various cmds and your disposal.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t-v\tVertical, displays commands one per line.\n");
  write("See also: man, help\n");
}

// XXX not sure on verbs vs cmds might want to merge them...
// might want to make emote's available as well with a flag... -e

void show_cmds( string dir) {
   string *names;
   mapping cmds;
   int c, d, sz;
   string * files;
   int i;
 
   cmds = ([ ]);
   files = get_dir( dir + "/*.c" )[0];
   for( i = sizeof( files ) - 1; i >= 0; i-- ) {
     cmds[files[i][..strlen(files[i])-3]] = dir;
   }

   names = map_indices( cmds );

   write ("Commands: " + dir + "\n");

   for( d = 0, sz = sizeof( names ); d < sz; d += col ) {
      int colnum;
      string line;

      line = "";

      for( colnum = 0; colnum < col; colnum++ ) {
         if( d + colnum < sz ) {
            line += ( names[d + colnum] + 
               ( col == 1 ? " (" + cmds[names[d+colnum]] + ")" : "" ) +
               "                                             " +
               "                         ")[0..(70/col)];
          }
      }
      write( line );
   }
}

void main( string str ) {
   string *path;
   int c, cmax;
   string race;
   string guild;
   string *guilds;

   if( str == "-v" ) {
      col = 1;
   } else {
      col = 4;
      if (str && str != "") {
         usage();
         return;
      }
   }

   path = this_player()->query_path();

   for ( c = sizeof( path ) - 1; c >= 0; c-- ) {
      show_cmds(path[c]);
   } 

   show_cmds("/cmds/verb");

   race = "/cmds/race/" + this_player()->query_race();
   if (file_exists(race) == -1) {
	show_cmds(race);
   }
   guilds = this_player()->query_guilds();

   if (guilds) {
         cmax = sizeof(guilds);
         for (c=0;c<cmax;c++) {
         guild= "/cmds/guild/" + guilds[c];
         if (file_exists(guild) == -1) {
             show_cmds(guild);
         }
      }
   }
}

