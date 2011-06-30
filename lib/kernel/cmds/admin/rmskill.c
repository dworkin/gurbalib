void usage() {
  write("Usage: rmskill [-h] SKILL\n");
  write("Delete the specified skill, SKILL.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main(string skill) {
  if (sscanf(skill, "-%s",skill)) {
     usage();
     return;
  }

  if( ( !skill ) || ( skill == "" ) ) {
    write( "You must provide the skill you want to remove as an argument." );
    return;
  }

  if( !SKILL_D->is_skill( skill ) ) {
    write( "Invalid skill." );
    return;
  }

  if( !require_priv( "system" ) ) {
    write("You must be admin to do that.");
    return;
  }

  SKILL_D->remove_skill( skill );
  write( "Skill removed." );
}
