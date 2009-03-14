int member_map( mixed item, mapping map ) {
  mixed *arr;

  arr = map_indices( map );
  if( member_array( item, arr ) > -1 )
    return( 1 );
  arr = map_values( map );
  if( member_array( item, arr ) > -1 )
    return( 1 );

  return( 0 );

}

