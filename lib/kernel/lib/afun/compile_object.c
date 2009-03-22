static object compile_object( string path, varargs string code ) {
  argcheck( path, 1, "string" );

  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }
  return driver->compile_object( path, code );
}

