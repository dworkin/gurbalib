
void main( string file ) {
  string *lines;
  string name;
  int i;

  if( file == "" ) 
    file = this_player()->query_env( "cwf" );

  if( file == "" ) {
    write( "Please specify a filename." );
    return;
  }

  name = normalize_path( file, this_player()->query_env( "cwd" ) );
  if( name == "" ) {
    write( "Access denied.\n" );
    return;
  }
  if( file_exists( name ) == 1 ) {
    lines = explode( read_file( name ), "\n" );
    for( i = 0; i < sizeof( lines ); i++ ) {
      out( lines[i] + "\n" );
    }
  }
}
