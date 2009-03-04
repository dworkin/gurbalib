mixed *query_verb_info( void ) {
  return( ({ "", "OBJI" }) );
}

mixed can_wield( void ) {
  return( "Wield what?" );
}

mixed can_wield_obj( object obj ) {
  object *wielded;

  if( !obj->is_wieldable() ) {
    return( "You can't wield that." );
  }
  if( obj->query_wielded() == 1 ) {
    return( "You're already wielding the " + obj->query_id() + "." );
  }

  wielded = this_player()->query_wielded();
  if( obj->query_wield_type() == "single" ) {
    if( sizeof( wielded ) >= 2 ) {
      return( "Your hands are full." );
    }
  } else {
    if( sizeof( wielded ) != 0 ) {
      return( "You're already wielding something else." );
    }
  }
  return( 1 );
}

mixed do_wield_obj( object obj ) {
  this_player()->targetted_action( obj->query_wield_message(), nil, obj );
  this_player()->do_wield( obj );
}
