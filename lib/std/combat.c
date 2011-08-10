static object *targets;
static int fighting;
static object target;

void decrease_hp( int hp );
int query_max_hp( void );
int query_hp( void );
int is_dead( void );
string query_hit_skill( void );
int query_skill( string skill );
int query_max_damage(void );
int query_min_damage( void );
int query_damage_bonus( void );
void learn_skill( string skill );
int query_hp();
int query_max_hp();

void create( void ) {
  targets = ({ });
  fighting = 0;
}

int is_fighting( void ) {
  return( fighting );
}

void halt_fight( void ) {
  fighting = 0;
  targets = ({ });
}

void die( void ) {
  object obj;


  obj = clone_object( "/domains/required/objects/corpse" );
  if( this_object()->is_player() ) {
     obj->set_name( capitalize(this_object()->query_name()) );
  } else {
     obj->set_name( "a " + this_object()->query_id() );
  }
  obj->move( this_object()->query_environment() );

  if( !this_object()->is_player() ) {
    EVENT_D->unsubscribe_event("heart_beat");
    this_object()->destruct();
  }
}

void receive_damage( object who, int dam, int type ) {
  this_object()->message( "%^RED%^You took " + dam + " damage from " + who->query_id() + ".%^RESET%^" );
  this_object()->decrease_hp( dam );
  if( is_dead() ) {
    this_object()->simple_action( "$N $vfall to the ground...dead." );
    this_object()->message( "You have died." );
    halt_fight();
    die();
  }
}

void damage_target( int dam ) {
  int target_hp;
  target_hp = target->query_hp();
  /* award expr for damage inflicted to target */
  if(dam > target_hp) {
    this_player()->increase_expr(target_hp);
  } else {
    this_player()->increase_expr(dam);
  }
  /* damage target */
  target->receive_damage( this_object(), dam, 0 );
}

int query_defense( void ) {
  int me;
  int i;
  object *armor;

  me = random( query_skill( "combat/defense" ) / 50 );
  me += this_object()->query_statbonus( "dex" );
  armor = this_object()->query_equipment();
  for( i = 0; i < sizeof( armor ); i++ ) {
    if( armor[i]->is_armor() ) {
      me+= armor[i]->query_ac();
    }
  }

  armor = this_object()->query_wielded();
  for( i = 0; i < sizeof( armor ); i++ ) {
    if( armor[i]->is_armor() ) {
      me+= armor[i]->query_ac();
    }
  }

  return( me );
}

void switch_to( object who ) {
  target = who;
}

int do_swing( int me ) {
  int opponent;
  int me_roll;
  int opponent_roll;

  me_roll = random( me + 1 );

  opponent = target->query_defense();
  opponent_roll = random( opponent + 1 );
  this_object()->message( "Roll [%^RED%^" + me_roll + "%^RESET%^/%^GREEN%^" + me + "%^RESET%^  vs %^RED%^" + opponent_roll + "%^RESET%^/%^GREEN%^" + opponent + "%^RESET%^]" );
  if( me_roll > opponent_roll ) {
    return( 1 );
  } 

  return( 0 );
}

void do_fight( void ) {
  int me;
  int i;
  object *weapons;
  int damage;
  
  if( target ) {
     
     if( target->query_environment() != this_object()->query_environment() || target->is_dead() ) {
	targets -= ({ target });
	if( sizeof( targets ) > 0 )
	   switch_to( targets[0] );
	else {
	   halt_fight();
	   return;
	}
     }
  } else {
    targets -= ({nil});
    if(sizeof(targets) > 0) {
      switch_to( targets[0] );
    } else {
      halt_fight();
      return;
    }
  }

  weapons = this_object()->query_wielded();
  if( sizeof( weapons ) == 0 ) {
    me = (query_skill( "combat/unarmed" ) / 50) + this_object()->query_statbonus("str");

    if( do_swing( me ) == 1 ) {
      damage = random( 3 ) + this_object()->query_statbonus("str");
/*      this_object()->message( "%^RED%^Hit for: " + damage + "%^RESET%^" ); */
      this_object()->targetted_action( "$N $vhit $T for " + damage +" damage.", target );
      damage_target( damage );
      if( ( query_skill( "combat/unarmed" ) ) 
	  + ( query_skill( "combat/unarmed" ) / 2 ) 
	  <= target->query_skill( "combat/defense" ) ) {
	learn_skill( query_hit_skill() );
	this_object()->message( "Learn: hit_skill, " + query_skill( "combat/unarmed" ) );
      }
      
    } else {
      this_object()->targetted_action( "$N $vmiss $T.", target );
      if( target->query_skill( "combat/defense" ) 
	  <= query_skill( "combat/unarmed" )
	  + query_skill( "combat/unarmed" ) / 2 ) {
	target->learn_skill( "combat/defense" );
      }
    }
  } else {
    for( i = 0; i < sizeof( weapons ); i++ ) {
      if( !weapons[i]->query_offensive() )
	continue;
      me = (query_skill( weapons[i]->query_weapon_skill() ) / 50 ) 
	 + this_object()->query_statbonus("str") 
	 + weapons[i]->query_hit_bonus();
      
      if( do_swing( me ) == 1 ) {
	damage = this_object()->query_statbonus("str")
	  + random( ( weapons[i]->query_max_damage() 
		      - weapons[i]->query_min_damage() ) ) 
	  + weapons[i]->query_min_damage();
	this_object()->message( "%^RED%^Hit for: " + damage + "%^RESET%^" );
	this_object()->targetted_action( "$N $v" + weapons[i]->query_weapon_action() + " $T for " + damage +" damage.", target );
	if( ( query_skill( weapons[i]->query_weapon_skill() ) ) 
	    + ( query_skill( weapons[i]->query_weapon_skill() ) / 2 ) 
	    <= target->query_skill( "combat/defense" ) ) {
	  learn_skill( weapons[i]->query_weapon_skill() );
	  this_object()->message( "Learn: hit_skill, " 
				  + query_skill( weapons[i]->query_weapon_skill() ) );
	}
        damage_target( damage );
	
      } else {
	this_object()->targetted_action( "$N $vmiss $T.", target );
	if( target->query_skill( "combat/defense" ) 
	    <= query_skill( weapons[i]->query_weapon_skill() ) 
	    + query_skill( weapons[i]->query_weapon_skill() ) / 2 ) {
	  target->learn_skill( "combat/defense" );
	  target->message( "Learn: defense, " + query_skill( "combat/defense" ) );
	}
      }
    }
  }

  this_object()->message( "%^CYAN%^HP[" + query_hp() + "/" + query_max_hp() + "]%^RESET%^" );
  if(!target || target->is_dead() ) {
    targets -= ({ target });
    if( sizeof( targets ) > 0 )
      switch_to( targets[0] );
    else
      halt_fight();
  }
}

void attacked_by( object who ) {
  if( !targets )
    targets = ({ });
  targets += ({ who });
  target = who;
  fighting = 1;
}

void attack( object who ) {
  if( !targets )
     targets = ({ });
  if( who->query_hp() < 1 )
     return;
            
  targets += ({ who });
  fighting = 1;
  target = who;
  who->attacked_by( this_object() );
  do_fight();
}


