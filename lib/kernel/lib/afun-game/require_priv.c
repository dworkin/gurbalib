nomask static int require_priv( string priv ) {
  if( !secure_d ) 
    secure_d = find_object( SECURE_D );
  
  if( !secure_d ) {
    return 0;
  }

  return secure_d->validate_stack( priv );
}
