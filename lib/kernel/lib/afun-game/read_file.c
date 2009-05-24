static string read_file(string file, varargs int offset, int size) {
  if( !valid( file, MODE_READ ) ) {
#ifdef ENABLE_STACK_SECURITY
    error( "Access to "+file+" denied" );   
#else
    console_msg("Access to "+file+" would have been denied, ignoring...\n");
#endif
  }

  return ::read_file( file, offset, size );
}
