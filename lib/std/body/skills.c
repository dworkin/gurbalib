mapping skills;
string hit_skill;

void create( void ) {
  if( !skills )
    skills = ([ ]);
}

void set_hit_skill( string skill ) {
  if( !SKILL_D->is_skill( skill ) ) {
    write( "Unknown skill : " + skill );
    return;
  }
  hit_skill = skill;
}

string query_hit_skill( void ) {
  if( !hit_skill )
    return( "combat/unarmed" );
  return( hit_skill );
}

void set_skill( string skill, int val ) {

  if( !SKILL_D->is_skill( skill ) ) {
    write( "Unknown skill : " + skill );
    return;
  }
  if( !skills )
    skills = ([ ]);

  skills[skill] = val;
}

int query_skill( string skill ) {
  if( !SKILL_D->is_skill( skill ) ) {
    write( "Unknown skill : " + skill );
    return( 0 );
  }
  if( !skills ) {
    skills = ([ ]);
    return 0;
    }
  if(!skills[skill])
    return 0;
  return( skills[skill] );
}

string *query_skills( void ) {
  if( !skills )
    skills = ([ ]);

  return( map_indices( skills ) );
}

void increase_skill( string skill, int val ) {
  if( !SKILL_D->is_skill( skill ) ) {
    write( "Unknown skill : " + skill );
    return;
  }
  if( !skills )
    skills = ([ ]);

  if( !skills[skill] )
    return;

  skills[skill] = skills[skill] + val;
}

void learn_skill( string skill ) {
  if( !SKILL_D->is_skill( skill ) ) {
    write( "Unknown skill : " + skill );
    return;
  }

  if( !skills )
    skills = ([ ]);

  /* Should players automatically learn new skills? */

  /*  if( !skills[skill] )
      return;
  */

  if( random( 5000 ) >= query_skill( skill ) ) {
    increase_skill( skill, 1 );
  }
}
