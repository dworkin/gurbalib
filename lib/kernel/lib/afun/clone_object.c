static object clone_object( string path ) {
  object ob, ed;
  string trace;
  string cloner;

  argcheck( path, 1, "string" );

  ed = find_object(ERROR_D);

  /*
   * yeah.. calling the error_d to get a formatted runtime trace.. no, we aren't
   * reporting an error here, just using one of its nice utility functions to get
   * a nicely formatted trace
   *
   */
  if(ed) trace = ed->format_runtime_error("Clone calltrace",::call_trace(),0,0,0);
  else trace = "No clone calltrace available\n";

  cloner = _owner;

  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }

  if(find_object(COMPILER_D)) {
    path = COMPILER_D->allow_object( path );
  }

  if( !(ob = find_object( path ) ) )
    ob = compile_object( path );

  ob = ::clone_object( ob );
  ob->_F_set_cloner(cloner,trace);
  return ob;
}

