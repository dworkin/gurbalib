void usage() {
  write("Usage: give [-h] OBJ1 [to] OBJ2\n");
  write("Allows you to give an object OBJ1 to OBJ2.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

string *query_verb_info() {
  return( ({ "", "OBJI", "OBJI to LIV" }) );
}

int can_give() {
  return 1;
}

int can_give_obj( object obj ) {
  return 1;
}

int can_give_obj_str_liv( object obj, string s, object liv ) {
   return( 1 );
}

void do_give() {
  write( "Give what to who?" );
  }

void do_give_obj(object obj) {
  if( obj->is_undroppable() ) {
this_player()->targetted_action( "$N $vare unable to give away $o.", nil, obj );
  return;
  }
  write( "Give " + obj->query_id() + " to who?" );
  }

void do_give_obj_str_liv( object obj, string s, object liv ) {
  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to give $o to $T.", liv, obj );
    return;
  }

  /* Should check if the target has room in it's inventory.*/
  if( !liv->is_container() )
    return;

  if( liv == this_player() ) {
    write( "What's the point of giving something to yourself?" );
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
  
  if( obj->move( liv ) ) {
    this_player()->targetted_action( "$N $vgive $o to $T.", liv, obj );
  } else {
    this_player()->targetted_action( "$N $vtry to give $o to $T, but $vfail.", liv, obj ); 
  }
}
