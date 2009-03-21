int member_array( mixed item, mixed *arr ) {
  int i, sz;

  argcheck( arr, 2, "array" );

  for( i=0, sz=sizeof( arr ); i < sz; i++ ) {
    if( arr[i] == item )
      return( i );
  }
  return( -1 );
}

