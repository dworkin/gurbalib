void main( string str ) {
  object ob;

  if( str == "" ) {
    if( this_user()->query_player()->is_possessing() ) {
      write( "Your release your grasp on " + this_player()->query_name() + "." );
      this_user()->query_player()->query_possessing()->set_possessor( nil );
      this_user()->query_player()->set_possessing( nil );
      return;
    } else {
      write( "Please specify what to possess.\n" );
      return;
    }
  }

  if( this_user()->query_player()->is_possessing() ) {
    write( "You can't possess more than one beeing at a time." );
    return;
  }

  ob = this_environment()->find_object( lowercase(str) );
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
    write( "You take control over the " + lowercase(str) + "." );
  } else {
    write( "You can't possess that." );
  }
}
