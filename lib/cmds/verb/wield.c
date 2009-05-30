string *query_verb_info() {
  return( ({ "", "OBJI" }) );
}

int can_wield() {
  return 1;
}

int can_wield_obj( object obj ) {
  return 1;
}

void do_wield() {
  write( "Wield what?" );
  }

void do_wield_obj( object obj ) {
  object *wielded;

  if( !obj->is_wieldable() ) {
    write( "You can't wield that." );
	return;
  }
  if( obj->query_wielded() == 1 ) {
    write( "You're already wielding the " + obj->query_id() + "." );
	return;
  }

  wielded = this_player()->query_wielded();
  if( obj->query_wield_type() == "single" ) {
    if( sizeof( wielded ) >= 2 ) {
      write( "Your hands are full." );
	  return;
    }
  } else {
    if( sizeof( wielded ) != 0 ) {
      write( "You're already wielding something else." );
	  return;
    }
  }
  this_player()->targetted_action( obj->query_wield_message(), nil, obj );
  this_player()->do_wield( obj );
}
