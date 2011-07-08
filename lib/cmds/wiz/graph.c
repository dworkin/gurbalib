void usage() {
  write("Usage: graph [-h] DIR\n");
  write("prints dot compatible output of a graph of the directory you " +
    "specify.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {

  if( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  str = normalize_path( str, this_player()->query_env( "cwd" ) );

  if( !arg || arg == "" ) {
    write( "Access denied.\n" );
    return;
  }

 if( strlen(arg) > 1 && arg[strlen(arg)-1] == '/' ) {
    arg = arg[..strlen(arg)-2];
  }
    
  if( file_exists( arg ) != -1 ) {
    write( "Dir not found.\n" );
    return;
  }

  /* Look at ls it does this and then does str + "/*"
     I don't think we need both... it's odd... */
  files = get_dir( str );
  if( !files ) {
    write( "No such dir.\n" );
    return;
  }

  /* do the work here... */
  /* XXX */ 
}
