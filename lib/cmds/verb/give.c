mixed *query_verb_info( void ) {
  return( ({ "", "OBJI", "OBJI to LIV" }) );
}

mixed can_give( void ) {
  return( "Give what to who?" );
}

mixed can_give_obj( object obj ) {
  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to give away $o.", nil, obj );
    return( 0 );
  }
  return( "Give " + obj->query_id() + " to who?" );
}

mixed can_give_obj_to_liv( object obj, string s, object liv ) {
  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to give $o to $T.", liv, obj );
    return( 0 );
  }

  /* Should check if the target has room in it's inventory.*/

  if( !liv->is_container() ) {
    return( 0 );
  }

  if( liv == this_player() )
    return( "What's the point of giving something to yourself?" );

  return( 1 );
}



mixed do_give_obj_to_liv( object obj, string s, object liv ) {
  if( obj->is_worn() ) {
    this_player()->do_remove( obj );
    this_player()->targetted_action( obj->query_remove_message(), nil, obj );
  }
  
  if( obj->is_wielded() ) {
    this_player()->do_unwield( obj );
    this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
  }
  
  if( obj->move( liv ) ) {
    this_player()->targetted_action( "$N $vgive $o to $T.", liv, obj );
  } else {
    this_player()->targetted_action( "$N $vtry to give $o to $T, but $vfail.", liv, obj ); 
  }
}
