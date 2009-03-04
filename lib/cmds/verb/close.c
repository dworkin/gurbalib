mixed *query_verb_info( void ) {
  return( ({ "", "OBJ", "OBJA" }) );
}

mixed can_close( void ) {
  return( "Close what?" );
}

mixed can_close_str( string str ) {
  if( lowercase(str) == "all" 
      || lowercase(str) == "everything" 
      || lowercase(str) == "all doors"
      || lowercase(str) == "every door" 
      )
    return( 1 );
  else
    return( "You can't seem to find the " + str + "." );
}

mixed can_close_obj( object obj ) {
  if( obj->is_closable() )
    return( 1 );
  return( "You can't open the " + obj->query_id() + "." );
}

mixed do_close_str( string str ) {
  object *inv;
  int i;

  if( lowercase(str) == "all" 
      || lowercase(str) == "everything" 
      ) {
    inv = this_environment()->query_inventory();
    for( i=0; i < sizeof( inv ); i++ ) {
      if( inv[i]->is_closable() ) {
	inv[i]->do_close( this_player() );
      }
    }
  } else if( lowercase(str) == "all doors"
	     || lowercase(str) == "every door" 
	     ) {
    inv = this_environment()->query_inventory();
    for( i=0; i < sizeof( inv ); i++ ) {
      if( inv[i]->is_closable() && inv[i]->is_door() ) {
	inv[i]->do_close( this_player() );
      }
    }
  } 
}

mixed do_close_obj( object obj ) {
  obj->do_close( this_player() );
}


