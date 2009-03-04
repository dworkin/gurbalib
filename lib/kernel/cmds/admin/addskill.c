void main( string str ) {

  if( SKILL_D->is_skill( str ) ) {
    this_player()->write( "Skill already exists." );
    return;
  }
    
  SKILL_D->add_skill( str );
  this_player()->write( "Skill added. " );
}