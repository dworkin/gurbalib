string *query_verb_info() {
  return( ({ "", "OBJI" }) );
}

int can_remove() {
  return 1;
}

int can_remove_obj( object obj ) {
  return 1;
}

void do_remove() {
  write( "Remove what?" );
  return;
  }

void do_remove_obj( object obj ) {
  if( !obj->is_worn() && !obj->is_wielded() ) {
    write( "You're not using the " + obj->query_id() + "." );
	return;
  }

  if( obj->is_cursed() ) {
    this_player()->targetted_action( "$N $vtry to remove $o, but $vfumble.", nil, obj );
    write( "Strange..." );
	return;
  }
  if( obj->is_wielded() ) {
    this_player()->do_unwield( obj );
    this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
  } else {
    this_player()->do_remove( obj );
    this_player()->targetted_action( obj->query_remove_message(), nil, obj );
  }
}
