void usage() {
  write("Usage: cmds [-h] [-v]\n");
  write("cmds lists the various cmds and your disposal.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t-v\tVertical, displays commands one per line.\n");
  write("See also: man, help\n");
}

// XXX make sure race, verbs and guild commands show up as well...
// might want to make emote's available as well with a flag... -e

void main( string str ) {
  string *path;
  string *names;
  mapping cmds;
  int c, d, sz, col;

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

  for( c = sizeof( path ) - 1; c >= 0; c-- ) {
    string * files;
    int i;

    cmds = ([ ]);
    files = get_dir( path[c] + "/*.c" )[0];
    for( i = sizeof( files ) - 1; i >= 0; i-- ) {
      cmds[files[i][..strlen(files[i])-3]] = path[c];
    }

    names = map_indices( cmds );

    write ("Commands: " + path[c] + "\n");

    for( d = 0, sz = sizeof( names ); d < sz; d += col ) {
      int colnum;
      string line;

      line = "";

      for( colnum = 0; colnum < col; colnum++ ) {
        if( d + colnum < sz ) {
          line += ( names[d + colnum] + 
             ( str == "-v" ? " (" + cmds[names[d+colnum]] + ")" : "" ) +
             "                                             " +
             "                         ")[0..(70/col)];
        }
      }
      write( line );
    }
  }
}

