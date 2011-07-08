void usage() {
  write("Usage: possess [-h] [MONSTER]\n");
  write("Allows you to possess a monster and control it.\n");
  write("If you type possess with no arguments you will stop possessing " +
    "an object.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object ob;

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( !str || str == "" ) {
    if( this_user()->query_player()->is_possessing() ) {
      write( "Your release your grasp on " + this_player()->query_name() + 
        "." );
      this_user()->query_player()->query_possessing()->set_possessor( nil );
      this_user()->query_player()->set_possessing( nil );
      return;
    } else {
      write( "Please specify what to possess.\n" );
      return;
    }
  }

  if( this_user()->query_player()->is_possessing() ) {
    write( "You can't possess more than one being at a time." );
    return;
  }

  ob = this_environment()->present( lowercase(str) );
  if( !ob ) {
    write( "You can't seem to find the " + lowercase(str) + "." );
    return;
  }

  if( ob->is_living() ) {
    if( ob->is_player() ) {
      write( "You can't possess other players." );
      return;
    }

    if( ob->is_possessed() ) {
      write( "You can't possess a creature someone is already possessing." );
      return;
    }

    this_user()->query_player()->set_possessing( ob );
    ob->set_possessor( this_user()->query_player() );
    write( "You take control over the " + lowercase(str) + ".\n" );
    write( "To stop type: possess\n" );
  } else {
    write( "You can't possess that." );
  }
}
