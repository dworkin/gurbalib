string *skills;

void save_me( void ) {
  save_object( "/daemons/data/skill_d.o" );
}

void restore_me( void ) {
  restore_object( "/daemons/data/skill_d.o" );
}

void create ( void ) {
  skills = ({ });
  restore_me();
}

void add_skill( string skill ) {
  if( !skills )
    skills = ({ });

  skill = lowercase( skill );

  skills -= ({ skill });
  skills += ({ skill });

  save_me();
}

void remove_skill( string skill ) {
  if( !skills )
    skills = ({ });

  skills -= ({ skill });
  save_me();
}

string *query_skills( void ) {
  return( skills );
}

int is_skill( string skill ) {
  if( member_array( skill, skills ) != -1 )
    return( 1 );
  return( 0 );
}