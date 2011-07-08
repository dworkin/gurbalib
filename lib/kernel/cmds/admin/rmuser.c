object lock;

void usage() {
  write("Usage: rmuser [-h] USER\n");
  write("Delete the specified user, USER.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX Fix it so it checks for valid user and tells you if your
// removing a non existing user

// XXX add it so it prompts you to remove their wizdir if wizard and or
// admin...

// XXX need to remove perms for the given user as well...
// if you remove a wizard it should remove that usernames perms.
// maybe add a check so you don't delete the last admin??

static void rmuser( string name ) {
  USER_D->delete_user( name );
}

void confirm_remove( string str ) {
  if( !lock || previous_object() != lock ) {
    return;
  }

  this_player()->input_to_object( this_object(), "confirm_remove" );
  write( "Removing " + name + ", are you sure? (y/n)" );
  return;
}

void main( string str ) {
  if( !str || str == "" ) {
    usage();
    return;
  }

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( !require_priv( "system" ) ) {
    write("You must be admin to do that.");
    return;
  }
  str = lowercase(str);

  if (this_player()->query_name == str) {
      write("You may not remove yourself.\n");
      return;
  }

  if( lock ) {
    write( lock->query_name() + " is currently using this command." );
    return;
  }

  lock = this_player();
  confirm_remove(str);
}

