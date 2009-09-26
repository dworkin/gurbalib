object lock;
string name;

static void rmuser( string name ) {
  USER_D->delete_user( name );
}

void confirm_remove( varargs string str ) {
  if( !lock || previous_object() != lock ) {
    return;
  }

  if( !str || !strlen( str ) ) {
    this_player()->input_to_object( this_object(), "confirm_remove" );
    write( "Removing " + name + ", are you sure? (y/n)" );
    return;
  }

  switch( lowercase( str[0..0] ) ) {
    case "y" :
      rmuser( name );
      write( "Ok." );
      break;
    default :
      write( "Aborted." );
      break;
  }
  name = nil;
  lock = nil;
}

void main( string str ) {
  if( !str || str == "" ) {
    write( "Useage: rmuser <name>\n" );
    return;
  }

  if( lock ) {
    write( lock->query_name() + " is currently using this command." );
    return;
  }

  if( SECURE_D->query_admin( this_player()->query_name() ) == 1 ) {
    lock = this_player();
    name = str;
    confirm_remove();
  } else {
    write( "You need admin priveleges to remove users.\n" );
  } 
}
