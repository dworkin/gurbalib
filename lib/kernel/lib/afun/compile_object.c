static object compile_object( string path, varargs string code ) {
  argcheck( path, 1, "string" );

  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }
  if(find_object(COMPILER_D) && !code) {
    path = COMPILER_D->allow_object( path );
  }
  return driver->compile_object( path, code );
}

