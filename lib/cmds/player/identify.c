void main( string str ) {
  object obj;
  object *wielded;

  obj = this_player()->present( lowercase( str ) );
  if( !obj ) {
    write( "Maybe you should get one first?" );
    return;
  }
	
	if( obj->query_detailed_desc() ) {
		write( obj->query_detailed_desc() );
	} else {
		write( "You discover nothing special" );
	}
}
