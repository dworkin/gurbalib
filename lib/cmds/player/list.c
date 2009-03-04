void main( string str ) {
  object vendor;
  object *objs;
  int i;

  if( this_environment()->is_storage() ) {
    write( this_environment()->query_stored_list() );
  } else {

    objs = this_environment()->query_inventory();

    for( i = 0; i < sizeof( objs ); i ++ ) {
      if( objs[i]->is_vendor() )
	vendor = objs[i];
    }
    if( !vendor ) {
      this_player()->write( "Perhaps you should try to do this somewhere else?" );
      return;
    }

    vendor->do_list( this_player() );
  }
}
