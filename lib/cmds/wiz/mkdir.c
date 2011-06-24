void usage() {
  write("Usage: mkdir [-h] [dir]\n");
  write("mkdir allows you to make a directory named [dir].\n";
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
  string file;

  if( !arg || arg == "" ) {
    usage();
    return;
  }

  file = normalize_path( arg, this_player()->query_env( "cwd" ) );
  if( !file || file == "" ) {
    write( "Permission denied.\n" );
    return;
  }
  
  if( !file_exists( file ) ) {
    if( !make_dir( file ) ) {
      write( "Unable to create directory.\n" );
      return;
    } else {
      write( "Directory created.\n" );
      return;
    }
  } else {
    write( "File or dir already exists.\n" );
  }

}
