string *query_verb_info() {
  return( ({ "", "OBJI in OBJ" }) );
}

int can_put() {
  return 1;
}

int can_put_obj_str_obj( object obj, string str, object target ) {
  return 1;
}

void do_put() {
  write( "Put what in where?" );
  }

void do_put_obj_str_obj( object obj, string str, object target ) {
  if( lowercase(str) != "in" ) {
    write( "Put what in where?" );
	return;
	}

  if( !target->is_container() ) {
    write( "You can't put anything in there." );
	return;
	}

  if( target->is_closed() ) {
    write( "It's not open." );
	return;
	}

  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to drop $p $o.", nil, obj );
    return;
  }
  
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
