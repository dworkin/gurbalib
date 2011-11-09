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

#define FIGHTING_TIMEOUT 300

// XXX Need to use endurance in combat.....

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

// XXX Need to work on this.... should move player to void...
// and drop money?  I think this should be in body and or living not combat...
void die( void ) {
  object obj;

  obj = clone_object( "/domains/required/objects/corpse" );
  if( this_object()->is_player() ) {
    obj->set_name( capitalize(this_object()->query_name()) );
    obj->move( this_object()->query_environment() );

    this_object()->move( "/domains/required/rooms/void" );
    EVENT_D->unsubscribe_event("heart_beat");
    this_object()->destruct();
  } else {
    obj->set_name( "a " + this_object()->query_id() );
    obj->move( this_object()->query_environment() );
  }
}

void receive_damage( object who, int dam, int type ) {
  this_object()->message( "%^RED%^You took " + dam + " damage from " + 
    who->query_id() + ".%^RESET%^" );
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
  int me, i;
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

int do_swing( int me ) {
  int opponent, me_roll, opponent_roll;

  me_roll = random( me + 1 );

  opponent = target->query_defense();
  opponent_roll = random( opponent + 1 );

  this_object()->message( "Roll [%^RED%^" + me_roll + "%^RESET%^/%^GREEN%^" + 
     me + "%^RESET%^  vs %^RED%^" + opponent_roll + "%^RESET%^/%^GREEN%^" + 
     opponent + "%^RESET%^]" );

  if( me_roll > opponent_roll ) return( 1 );
  return( 0 );
}

object get_target(object targ) {
   int i, max;

   if (targ) {
      if (targ->is_dead()) {
        targets -= ({ targ });
        if (sizeof(targets) == 0) fighting = 0;
      } else if (targ->query_environment() == 
         this_object()->query_environment()) {
         fighting = FIGHTING_TIMEOUT;
         return targ;
      }
   }
   max = sizeof(targets);
   for(i=0;i<max;i++) {
      if (targets[i] && targets[i]->is_dead()) {
         targets -= ({ targets[i] });
         if (sizeof(targets) == 0) {
            fighting = 0;
            i = max;
         }
      }
      if (targets[i] && (targets[i]->query_environment() == 
         this_object()->query_environment())) {
         fighting = FIGHTING_TIMEOUT;
         return targets[i];
      }
   }
   fighting = fighting -1;
   if (fighting < 1) {
      targets = ({ });
      write("You give up fighting your attacker.\n");
   }
   return nil;
}

void attack_with(string skill, object weapon, object target) {
   int me, tmp, damage;

   if (!weapon) {
      me = (query_skill( "combat/unarmed" ) / 50) + 
        this_object()->query_statbonus("str");
   } else {
      me = (query_skill( weapon->query_weapon_skill() ) / 50 ) 
	 + this_object()->query_statbonus("str") 
	 + weapon->query_hit_bonus();
   }
   if( do_swing( me ) == 1 ) {
      if (!weapon) {
         damage = random( 3 ) + this_object()->query_statbonus("str");
         tmp = query_skill( "combat/unarmed" ) +
	    query_skill( "combat/unarmed" ) / 2;
         if (tmp <= target->query_skill( "combat/defense" ) ) {
	    learn_skill( query_hit_skill() );
	    this_object()->message( "Learn: hit_skill, " + 
               query_skill( "combat/unarmed" ) );
         }

         this_object()->targetted_action( "$N $vhit $T.", target );

      } else {
	 damage = this_object()->query_statbonus("str") + 
	    random( ( weapon->query_max_damage() - 
            weapon->query_min_damage() ) )  +
	    weapon->query_min_damage();
         tmp = query_skill( weapon->query_weapon_skill() ) +
            query_skill( weapon->query_weapon_skill() ) / 2;
         if (tmp <= target->query_skill( "combat/defense" ) ) {
	    learn_skill( weapon->query_weapon_skill() );
	    this_object()->message( "Learn: hit_skill, " +
	       query_skill( weapon->query_weapon_skill() ) );
         }

         this_object()->targetted_action( "$N " + 
            weapon->query_weapon_action() + " $T with a " + 
            weapon->query_id() + ".", target );
      }

      damage_target( damage );
   } else {
      this_object()->targetted_action( "$N $vmiss $T.", target );

      if (!weapon) {
         tmp = query_skill( "combat/unarmed" ) +
	    query_skill( "combat/unarmed" ) / 2;
      } else {
         tmp = query_skill( weapon->query_weapon_skill() ) +
            query_skill( weapon->query_weapon_skill() ) / 2;
      }
      if( target->query_skill( "combat/defense" ) <= tmp) {
	  target->learn_skill( "combat/defense" );
	  target->message( "Learn: defense, " + 
             query_skill( "combat/defense" ) );
      }
   }
}

void do_fight( void ) {
  int i;
  object *weapons;
  
  target = get_target(target);

  if (target) {
     weapons = this_object()->query_wielded();

     if( sizeof( weapons ) == 0 ) {
        attack_with("combat/unarmed",nil,target);
     } else {
        for( i = 0; i < sizeof( weapons ); i++ ) {
           if( !weapons[i]->query_offensive() ) continue;
           attack_with(weapons[i]->query_weapon_skill(),weapons[i],target);
        }
     }

     this_object()->message( "%^CYAN%^HP[" + query_hp() + "/" + 
        query_max_hp() + "]%^RESET%^" );
  }
}

void attacked_by( object who ) {
  if( !targets ) targets = ({ });
  targets += ({ who });
  target = who;
  fighting = FIGHTING_TIMEOUT;
}

void attack( object who ) {
  if( !targets ) targets = ({ });
  if( who->query_hp() < 1 ) return;
            
  targets += ({ who });
  fighting = FIGHTING_TIMEOUT;
  target = who;
  who->attacked_by( this_object() );
  do_fight();
}

