void main(string skill) {
  if( ( !skill ) || ( skill == "" ) ) {
    write( "You must provide the skill you want to remove as an argument." );
    return;
  }

  if( !SKILL_D->is_skill( skill ) ) {
    write( "Invalid skill." );
    return;
  }

  SKILL_D->remove_skill( skill );
  write( "Skill removed." );
}
