string *query_verb_info() {
  return( ({ "", "OBJ", "OBJA" }) );
}

int can_open() {
  return 1;
}

int can_open_str( string str ) {
  return 1;
}

int can_open_obj( object obj ) {
  return 1;
}

void do_open() {
  write( "Open what?" );
  }

void do_open_str( string str ) {
  object *inv;
  int i;
  
  if( lowercase(str) != "all" 
      && lowercase(str) != "everything" 
      && lowercase(str) != "all doors"
      && lowercase(str) != "every door" 
      ) {
    write( "You can't seem to find the " + str + "." );
	return;
	}

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

void do_open_obj( object obj ) {
  if( !obj->is_openable() ) {
     write( "You can't open the " + obj->query_id() + "." );
	 return;
  }
  obj->do_open( this_player() );
}


