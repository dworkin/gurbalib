void main( string dir ) {
  string error;

  error = this_environment()->body_exit( this_player(), dir );

  if( error )
    write( error );
}

