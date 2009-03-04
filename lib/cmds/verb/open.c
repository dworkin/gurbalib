mixed *query_verb_info( void ) {
  return( ({ "", "OBJ", "OBJA" }) );
}

mixed can_open( void ) {
  return( "Open what?" );
}

mixed can_open_str( string str ) {
  if( lowercase(str) == "all" 
      || lowercase(str) == "everything" 
      || lowercase(str) == "all doors"
      || lowercase(str) == "every door" 
      )
    return( 1 );
  else
    return( "You can't seem to find the " + str + "." );
}

mixed can_open_obj( object obj ) {
  if( obj->is_openable() )
    return( 1 );
  return( "You can't open the " + obj->query_id() + "." );
}

mixed do_open_str( string str ) {
  object *inv;
  int i;

  if( lowercase(str) == "all" 
      || lowercase(str) == "everything" 
      ) {
    inv = this_environment()->query_inventory();
    for( i=0; i < sizeof( inv ); i++ ) {
      if( inv[i]->is_openable() ) {
	inv[i]->do_open( this_player() );
      }
    }
  } else if( lowercase(str) == "all doors"
	     || lowercase(str) == "every door" 
	     ) {
    inv = this_environment()->query_inventory();
    for( i=0; i < sizeof( inv ); i++ ) {
      if( inv[i]->is_openable() && inv[i]->is_door() ) {
	inv[i]->do_open( this_player() );
      }
    }
  } 
}

mixed do_open_obj( object obj ) {
  obj->do_open( this_player() );
}


