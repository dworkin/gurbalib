static object compile_object( string path ) {
  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }
  return DRIVER->compile_object( path );
}

