int strstr( string search, string what ) {
  int i;

  for( i = 0; i < (strlen( search ) - ( strlen( what ) - 1 )); i++ ) {
    if( search[i..(i+strlen(what)-1)] == what )
      return i;
  }
  return( -1 );
}

