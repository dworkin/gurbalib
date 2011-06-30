void usage() {
  write("Usage: addskill [-h] SKILL\n");
  write("Add the specified skill, SKILL.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: rmskill, skills\n");
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

  if( SKILL_D->is_skill( str ) ) {
    this_player()->write( "That skill already exists." );
    return;
  }
  SKILL_D->add_skill( str );
  write( "Skill added. " );
}
