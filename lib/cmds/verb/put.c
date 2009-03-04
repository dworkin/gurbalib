mixed *query_verb_info( void ) {
  return( ({ "", "OBJI in OBJ" }) );
}

mixed can_put( void ) {
  return( "Put what in where?" );
}

mixed can_put_obj_in_obj( object obj, string str, object target ) {
  if( lowercase(str) != "in" )
    return( "Put what in where?" );

  if( !target->is_container() )
    return( "You can't put anything in there." );

  if( target->is_closed() )
    return( "It's not open." );

  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to drop $p $o.", nil, obj );
    return( 0 );
  }
  return( 1 );
}


mixed do_put_obj_in_obj( object obj, string str, object target ) {

  if( obj->is_worn() ) {
    this_player()->do_remove( obj );
    this_player()->targetted_action( obj->query_remove_message(), nil, obj );
  }

  if( obj->is_wielded() ) {
    this_player()->do_unwield( obj );
    this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
  }

  if( obj->move( target ) ) {
    this_player()->targetted_action( "$N $vput $o in $o1.", nil, obj, target );
  } else {
    this_player()->targetted_action( "$N $vtry to put $o in $o1, but $vfail.", nil, obj, target );
  }
}
