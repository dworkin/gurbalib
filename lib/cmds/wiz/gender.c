void main( string str ) {
  if( !str || str == "" ) {
    write( "Usage: gender <male/female>\n" );
    return;
  }

  if( lowercase( str ) == "female" ) {
    this_player()->set_gender( "female" );
    write( "You are now female.\n" );
    this_player()->save_me();
  } else if (lowercase( str ) == "male" ) {
    this_player()->set_gender( "male" );
    write( "You are now male.\n" );
    this_player()->save_me();
  } else {
    write( "Please use \"male\" or \"female\" as argument.\n" );
  }
}
