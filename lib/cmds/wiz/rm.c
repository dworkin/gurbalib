void usage() {
  write("Usage: rm [-h] FILE\n");
  write("Remove a file or directory FILE.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
  string file;

  if( !arg || arg == "" ) {
    write( "Please specify filename to rm." );
    return;
  }
  if (sscanf(arg, "-%s",arg)) {
     usage();
     return;
  }

  file = normalize_path( arg, this_player()->query_env("cwd") );
  if( !file || file == "" ) {
    write( arg + ": Permission denied.\n" );
    return;
  }

  if( file_exists( file ) == -1 ) {
    if( !remove_dir( file ) ) {
      write( arg + ": Not empty.\n" );
    } else {
      write( "Deleted.\n" );
    }
  } else if( file_exists( file ) ) {
    if( !remove_file( file ) ) {
      write( arg + ": Unable to delete.\n" );
    }
  } else {
    write( arg + ": Not found.\n" );
  }
}
