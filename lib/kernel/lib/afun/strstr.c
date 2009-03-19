int strstr( string search, string what ) {
  int i, lw, ls;

  ls = strlen( search );
  lw = strlen( what ) - 1;
  for( i = 0; i < (ls - lw); i++ ) {
    if( search[i..(i+lw)] == what )
      return i;
  }
  return( -1 );
}

