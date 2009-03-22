static object find_object(string path) {
  if(::find_object(COMPILER_D)) {
    path = COMPILER_D->allow_object( path );
  }
  return ::find_object( path );
}

