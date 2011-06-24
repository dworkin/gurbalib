void usage() {
  write("Usage: cmds [-h] [-v]\n");
  write("cmds lists the various cmds and your disposal.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t-v\tVertical, displays commands one per line.\n");
}

void main( string str ) {
  string *path;
  string *names;
  mapping cmds;
  int c, sz, col;

  cmds = ([ ]);

  path = this_player()->query_path();

  if(!query_wizard( this_player() ) ) {
    str = "";
  }

  for( c = sizeof( path ) - 1; c >= 0; c-- ) {
    string * files;
    int i;

    files = get_dir( path[c] + "/*.c" )[0];
    for( i = sizeof( files ) - 1; i >= 0; i-- ) {
      cmds[files[i][..strlen(files[i])-3]] = path[c];
    }
  }

  names = map_indices( cmds );
  if( str == "-v" ) {
    col = 1;
  } else {
    col = 4;
  }

  for( c = 0, sz = sizeof( names ); c < sz; c += col ) {
    int colnum;
    string line;

    line = "";

    for( colnum = 0; colnum < col; colnum++ ) {
      if( c + colnum < sz ) {
        line += (
          names[c + colnum] + 
          ( str == "-v" ? " (" + cmds[names[c+colnum]] + ")" : "" ) +
          "                                                                      ")[0..(70/col)];
      }
    }
    write( line );
  }
}
      
