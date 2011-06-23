string *query_verb_info() {
  return( ({ "", "STR", "OBJ", "at OBJ", "LIV", "at LIV", "OBJA", "in OBJ" }) );
}

int can_look() {
  return( 1 );
}

int can_look_str( string str ) {
  return 1;
}

int can_look_obj( object obj ) {
  return( 1 );
}

int can_look_liv( object obj ) {
  return( 1 );
}

int can_look_str_obj( string str, object obj ) {
  return 1;
}

int can_look_str_liv( string str, object obj ) {
  return 1;
}

void do_look() {
  this_environment()->event( "body_look", this_player() );
  if( this_player()->is_player() == 1 ) {
    if( this_player()->query_env( "show_location" ) ) 
      write( "%^BOLD%^" + this_environment()->file_name() + "%^RESET%^" );
  }
  write( this_environment()->query_desc() );
}

void do_look_str( string str ) {
  if( member_array( str, this_environment()->query_items() ) == -1 ) {
    write("Look at what?" );
	return;
	}
  this_environment()->tell_room( this_player(), capitalize( this_player()->query_name() ) + " looks at the " + lowercase(str) + ".\n" );
  write( this_environment()->query_item( str ) );
}

void do_look_obj( object obj ) {
  int i;
  int flag;
  object *objs;
  this_environment()->event( "body_look_at", this_player(), obj );
  this_environment()->tell_room( this_player(), capitalize( this_player()->query_name() ) + " looks at the " + obj->query_id() + ".\n" );
  write( obj->query_long() );
  if( obj->is_closed() ) {
    write( "It is closed." );
  } else if( obj->is_container() ) {
    flag = 0;
    objs = obj->query_inventory();
    write( " \nIt contains:\n" );
    
    for( i = 0; i < sizeof( objs ); i++ ) {
      if( objs[i]->query_adj() != "" ) 
	write( "  " + objs[i]->query_adj() + " " + objs[i]->query_id() 
	       + "\n" );
      else
	write( "  " + objs[i]->query_id() + "\n" );
    }
  }
}

void do_look_liv( object obj ) {
  int i;
  int flag;
  object *objs;

  this_environment()->tell_room( this_player(), capitalize( this_player()->query_name() ) + " looks at " + capitalize( obj->query_id() ) + ".\n" );
  write( obj->query_long() );
  write( capitalize( obj->query_gender_pronoun()) + " is " + obj->query_gender() + ".\n" );
  write( capitalize( obj->query_gender_pronoun()) + " is " + article( obj->query_race() ) + " " + obj->query_race() + ".\n" );
  
  flag = 0;
  objs = obj->query_inventory();
  
  
  if (obj->query_gender() == "male") {
    write( " \nHe is using:\n" );
  } else if (obj->query_gender() == "female") {
    write( " \nShe is using:\n" );
  } else {
    write( " \nIt is using:\n" );
  }
  
  for( i = 0; i < sizeof( objs ); i++ ) {
    if( objs[i]->is_worn() ) {
      write( "  " + objs[i]->query_id() + " %^CYAN%^[" + objs[i]->query_wear_position() + "]%^RESET%^\n" );
      flag = 1;
    } else if( objs[i]->is_wielded() ) {
      write( "  " + objs[i]->query_id() + " %^CYAN%^[" + objs[i]->query_wield_position() + "]%^RESET%^\n" );
      flag = 1;
    }
  }
  if( flag == 0 ) {
    write( "  Nothing." );
  }
}

void do_look_str_obj( string str, object obj ) {
  if( str != "at" && str != "in" ) {
    write("Huh?");
	return;
	}
  if(str == "in" && !obj->is_container() ) {
      write( "You can't look in the " + obj->query_id() );
	  return;
	  }
  }

void do_look_str_liv( string str, object obj ) {
  int i;
  int flag;
  object *objs;
  
  if( str != "at" ) {
    write("Huh?");
	return;
	}
  if( str == "in" ) {
    write( "Pervert..." );
	return;
  }
  
  this_environment()->tell_room( this_player(), capitalize( this_player()->query_name() ) + " looks at " + capitalize( obj->query_id() ) + ".\n" );
  write( obj->query_long() );
  write( capitalize( obj->query_gender_pronoun()) + " is " + obj->query_gender() + ".\n" );
  write( capitalize( obj->query_gender_pronoun()) + " is " + article( obj->query_race() ) + " " + obj->query_race() + ".\n" );
  
  flag = 0;
  objs = obj->query_inventory();
  
  
  if (obj->query_gender() == "male") {
    write( " \nHe is using:\n" );
  } else if (obj->query_gender() == "female") {
    write( " \nShe is using:\n" );
  } else {
    write( " \nIt is using:\n" );
  }
  
  for( i = 0; i < sizeof( objs ); i++ ) {
    if( objs[i]->is_worn() ) {
      write( "  " + objs[i]->query_id() + " %^CYAN%^[" + objs[i]->query_wear_position() + "]%^RESET%^\n" );
      flag = 1;
    } else if( objs[i]->is_wielded() ) {
      write( "  " + objs[i]->query_id() + " %^CYAN%^[" + objs[i]->query_wield_position() + "]%^RESET%^\n" );
      flag = 1;
    }
  }
  if( flag == 0 ) {
    write( "  Nothing." );
  }
}


