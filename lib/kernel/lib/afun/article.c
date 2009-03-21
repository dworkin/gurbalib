string article( string name ) {
  argcheck( name, 1, "string" );

  if( lowercase( name ) == "hour" )
    return( "an" );

  switch( name[0] ) {
  case 'a':
  case 'e':
  case 'i':
  case 'o':
  case 'u':
    return( "an" );
  default:
    return( "a" );
  }
}

