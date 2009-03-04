static int open_state;
static string open_message;
static string close_message;
static string open_desc;
static string closed_desc;

int is_openable( void ) {
  return( 1 );
}

int is_closable( void ) {
  return( 1 );
}

int can_open( object who ) {
    return( 1 );
}

int is_open( void ) {
  return( open_state == 1 );
}

int is_closed( void ) {
  return( open_state == 0 );
}

int can_close( object who ) {
  return( 1 );
}

void set_open_message( string str ) {
  open_message = str;
}

void set_close_message( string str ) {
  close_message = str;
}

string query_open_message( void ) {
  if( !open_message || open_message == "" ) {
    open_message = "$N $vopen $o.";
  }
  return( open_message );
}

string query_close_message( void ) {
  if( !close_message || close_message == "" ) {
    close_message = "$N $vclose $o.";
  }
  return( close_message );
}

void set_open_description( string str ) {
  open_desc = str;
}

void set_closed_description( string str ) {
  closed_desc = str;
}

string query_open_description( void ) {
  return( open_desc );
}

string query_closed_description( void ) {
  return( closed_desc );
}

void update_description( void ) {

  if( !open_desc || open_desc == "" ) {
      open_desc = this_object()->query_brief() + " %^GREEN%^[open]%^RESET%^";
  }

  if( !closed_desc || closed_desc == "" ) {
    closed_desc = this_object()->query_brief() + " %^RED%^[closed]%^RESET%^";
  }
  
  if( open_state == 1 ) {
    this_object()->set_in_room_desc( query_open_description() );
  } else {
    this_object()->set_in_room_desc( query_closed_description() );
  }
}


void set_open_state( int state ) {
  open_state = state;
  if( state == 1 ) 
    this_object()->other_action( this_object(), "$N $vopen." );
  else
    this_object()->other_action( this_object(), "$N $vclose." );
    
  update_description();
}

int query_open_state( int state ) {
  return( open_state );
}

int do_open( object who ) {
  if( open_state == 1 ) {
    write( "It's already open." );
    return( 0 );
  }
  open_state = 1;
  update_description();
  if( who ) {
    who->targetted_action( query_open_message(), nil, this_object() );
  } else {
    this_object()->other_action( this_object(), "$N $vopen." );
  }
}

int do_close( object who ) {
  if( !open_state ) {
    write( "It's already closed." );
    return( 0 );
  }
  open_state = 0;
  update_description();
  if( who ) {
    who->targetted_action( query_close_message(), nil, this_object() );
  } else {
    this_object()->other_action( this_object(), "$N $vclose." );
  }
}

