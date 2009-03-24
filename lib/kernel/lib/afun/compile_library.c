static int compile_library( string path, varargs string code ) {
  argcheck( path, 1, "string" );

  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }

  if(find_object(COMPILER_D)) {
    path = COMPILER_D->allow_inherit( path , nil );
  }

  if(path) {
    if( ::find_object( path ) ) {
      destruct_object( ::find_object( path ) );
    }

    driver->compile_object( path, code );
    return 1;
  }
}

