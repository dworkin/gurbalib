/* Command to copy a file 
 * Fudge
 */

void main( string str ) {
  string file;
  string dest;
  string file_name;
  string where;
  string *parts;
  string in;

  if( !str || str == "" || ( sscanf( str, "%s %s", str, where ) != 2 ) ) {
    write( "Please specify a source and a destination." );
    return;
  }

  file = normalize_path( str, this_player()->query_env( "cwd" ) );
  if( !file || file == "" ) {
    write( file + ": Permission denied." );
    return;
  }

  if( file_exists( file ) == -1 ) {
    write( file + ": Unable to copy directories." );
    return;
  }

  if( !file_exists( file ) ) {
    write( file + ": File doesn't exist." );
    return;
  }

  parts = explode( file, "/" );
  file_name = parts[ sizeof( parts ) - 1 ];

  dest = normalize_path( where, this_player()->query_env( "cwd" ) );
  if( !dest || dest == "" ) {
    write( dest + ": Permission denied." );
    return;
  }

  if( file_exists( dest ) == -1 ) {
    if( dest[strlen( dest ) -1] != '/' ) {
      dest += "/";
    }
    
    dest += file_name;
  }

  if( file_exists( dest ) == -1 ) {
    write( dest + ": Unable to create destination." );
    return;
  }

  if( file_exists( dest ) > 0 ) {
    remove_file( dest );
  }

  in = read_file( file );
  write_file( dest, in );

}
