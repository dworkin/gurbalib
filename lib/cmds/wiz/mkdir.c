void main( string arg ) {
  string file;

  if( !arg || arg == "" ) {
    write( "Please specify the name of the new dir." );
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
