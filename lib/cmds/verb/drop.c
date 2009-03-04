mixed *query_verb_info( void ) {
  return( ({ "", "OBJI", "OBJA" }) );
}

mixed can_drop( void ) {
  return( "Drop what?" );
}

mixed can_drop_str( string str ) {
  if( lowercase(str) == "all" || lowercase(str) == "everything" )
    return( 1 );
  else
    return( "You can't seem to find the " + str + "." );
}

mixed can_drop_obj( object obj ) {
  if( obj->is_undroppable() ) {
    this_player()->targetted_action( "$N $vare unable to drop $o.", nil, obj ); 
    return( 0 );
  }
  return( 1 );
}

mixed do_drop_str( string str ) {
  object *inv;
  int i;

  inv = this_player()->query_inventory();
  for( i=0; i < sizeof( inv ); i++ ) {
    if( inv[i]->is_worn() ) {
      this_player()->do_remove( inv[i] );
      this_player()->targetted_action( inv[i]->query_remove_message(), nil, inv[i] );
    }
    
    if( inv[i]->is_wielded() ) {
      this_player()->do_unwield( inv[i] );
      this_player()->targetted_action( inv[i]->query_unwield_message(), nil, inv[i] );
    } 

    if( inv[i]->is_undroppable() ) {
      this_player()->targetted_action( "$N $vare unable to drop $o.", nil, inv[i] ); 
      return(0);
    }
    if( inv[i]->move( this_environment() ) ) {
      this_player()->targetted_action( "$N $vdrop $o.", nil, inv[i] );
    } 
    else {
      this_player()->targetted_action( "$N $vtry to drop $o, but $vfail.", nil, inv[i] ); 
    }
  }
} 

mixed do_drop_obj( object obj ) {
  if( obj->is_worn() ) {
    this_player()->do_remove( obj );
    this_player()->targetted_action( obj->query_remove_message(), nil, obj );
  }

  if( obj->is_wielded() ) {
    this_player()->do_unwield( obj );
    this_player()->targetted_action( obj->query_unwield_message(), nil, obj );
  }
  
  if( obj->move( this_environment() ) ) {
    this_player()->targetted_action( "$N $vdrop $o.", nil, obj );
  } else {
    this_player()->targetted_action( "$N $vtry to drop $o, but $vfail.", nil, obj ); 
  }
}
