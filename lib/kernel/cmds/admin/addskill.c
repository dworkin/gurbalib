void main( string str ) {
  if( !str || str == "" ) {
    write("You must provide the name of a skill to add.");
    return;
  }
  if( SKILL_D->is_skill( str ) ) {
    this_player()->write( "That skill already exists." );
    return;
  }
  SKILL_D->add_skill( str );
  write( "Skill added. " );
}
