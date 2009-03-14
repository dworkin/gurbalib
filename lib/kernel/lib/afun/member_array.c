int member_array( mixed item, mixed *arr ) {
  int i;

  for( i=0; i < sizeof( arr ); i++ ) {
    if( arr[i] == item )
      return( i );
  }
  return( -1 );
}

