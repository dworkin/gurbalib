static object compile_object( string path, string code... ) {
  if( code && sizeof( code ) ) {
    if( !valid_write( path ) ) {
      error("Permission denied");
    }
  } else {
    if( !valid_read( path ) ) {
      error("Permission denied");
    }
  }

  return ::compile_object( path, code... );
}
