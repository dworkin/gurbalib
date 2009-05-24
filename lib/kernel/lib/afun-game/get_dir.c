static mixed **get_dir( string file ) {
  if( !valid( file, MODE_READ ) ) {
#ifdef ENABLE_STACK_SECURITY
    error( "Access to "+file+" denied" );
#else
    console_msg("Access to "+file+" would have been denied, ignoring...\n");
#endif
  }

  return ::get_dir( file );
}
