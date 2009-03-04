mixed *query_verb_info( void ) {
  return( ({ "", "OBJI" }) );
}

mixed can_remove( void ) {
  return( "Remove what?" );
}

mixed can_remove_obj( object obj ) {

  if( !obj->is_worn() && !obj->is_wielded() ) {
    return( "You're not using the " + obj->query_id() + "." );
  }

  if( obj->is_cursed() ) {
    this_player()->targetted_action( "$N $vtry to remove $o, but $vfumble.", nil, obj );
    return( "Strange..." );
  }

  return( 1 );
}

mixed do_remove_obj( object obj ) {
  if( obj->is_wielded() ) {
    this_player()->do_unwield( obj );
    this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
  } else {
    this_player()->do_remove( obj );
    this_player()->targetted_action( obj->query_remove_message(), nil, obj );
  }
}
