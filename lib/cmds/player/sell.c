/* Created by Fudge */

void main( string str ) {
  object *objs;
  object obj;
  int i;

  if( !str || str == "" ) {
    write( "Sell what?" );
    return;
  }

  obj = this_player()->present( str ); 
  if( obj ) {
    /* Found the item */

    objs = this_environment()->query_inventory();
    for( i = 0; i < sizeof( objs ); i++ ) {
      if( objs[i]->is_vendor() == 1 ) {
	/* Found the shopkeeper */
	
	if( obj->is_worn() ) {
	  this_player()->do_remove( obj );
	  this_player()->targetted_action( obj->query_remove_message(), nil, obj );
	}
	
	if( obj->is_wielded() ) {
	  this_player()->do_unwield( obj );
	  this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
	}
	
	if( obj->is_undroppable() ) {
	  this_player()->targetted_action( "$N $vare unable to let go of $o.", nil, obj ); 
    return;
	} 
	
	objs[i]->do_buy( this_player(), obj );
	return;
	
      }
    }
    write( "Sell to who?" );
  }
  write( "You don't have that." );
}
