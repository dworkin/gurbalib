mixed *query_verb_info( void ) {
  return( ({ "", "OBJE", "LIV", "OBJC from OBJ", "OBJA" }) );
}

mixed can_get( void ) {
  return( "Get what?" );
}

mixed can_get_str( string str ) {
  if( lowercase(str) == "all" || lowercase(str) == "everything" )
    return( 1 );
  else
    return( "You can't seem to find the " + str + "." );
}

mixed can_get_obj( object obj ) {
  if( obj->is_gettable() )
    return( 1 );
  return( "You can't get the " + obj->query_id() + "." );
}

mixed can_get_liv( object liv ) {
  return( "You can't get that." );
}

mixed can_get_obj_from_obj( object target, string s, object obj ) {
  if( s == "from" && obj->is_container() ) {
    if( obj->is_closed() ) {
      return( "It's closed." );
    }
    return( 1 );
  }
  return( "You can't get " + target->query_id() + " from " + obj->query_id() + "." );
}

mixed do_get( void ) {
  write( "You get something. Report this to a wiz." );
}

mixed do_get_str( string str ) {
  object *inv;
  int i;

  inv = this_environment()->query_inventory();
  for( i=0; i < sizeof( inv ); i++ ) {
    if( inv[i]->is_gettable() ) {
      if( inv[i]->move( this_player() ) ) {
	this_player()->targetted_action( "$N $vpick up $o.", nil, inv[i] );
      } 
      else {
	this_player()->targetted_action( "$N $vtry to pick up $o, but $vfail.", nil, inv[i] ); 
      }
    } 
    else {
      if( !inv[i]->is_player() ) {
	this_player()->targetted_action( "$N $vare unable to get $o.", nil, inv[i] ); 
      }
    }
  } 
}

mixed do_get_obj( object obj ) {
  if( obj->move( this_player() ) ) {
    this_player()->targetted_action( "$N $vpick up $o.", nil, obj );
  }
  else {
    this_player()->targetted_action( "$N $vtry to pick up $o, but $vfail.", nil, obj ); 
  }
}

mixed do_get_liv( object obj ) {
  write( "You get the " + obj->query_id() + ", report to Fudge." );
}

mixed do_get_obj_from_obj( object target, string s, object obj ) {
  int    i;
  object *inv;

  if( s == "all" || s == "everything" ) {
    inv = obj->query_inventory();
    for( i = 0; i < sizeof( inv ); i ++ ) {
      if( inv[i]->move( this_player() ) ) {
	this_player()->targetted_action( "$N $vget $o from $o1.", nil, inv[i], obj );
      } else {
	this_player()->targetted_action( "$N $vtry to get $o from $o1, but $vfail.", nil, inv[i], obj );
      }
    }
  } else {
    if( target->move( this_player() ) ) {
      this_player()->targetted_action( "$N $vget $o from $o1.", nil, target, obj );
    } else {
      this_player()->targetted_action( "$N $vtry to get $o from $o1, but $vfail.", nil, target, obj );
    }
  }
}

