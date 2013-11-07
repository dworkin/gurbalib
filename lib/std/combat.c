static object *targets;
static int fighting;
static object target;
int kills;
mapping killed_by;

#define FIGHTING_TIMEOUT 300
/* Ammount of Endurance required to Attack */
#define ATTACK_COST 1

/* Uncomment this to get extra info in combat */
/* #define DEBUG 1 */

void create(void) {
   targets = ( { } );
   fighting = 0;
}

int is_fighting(void) {
   return fighting;
}

mapping query_killed_by() {
   if (!killed_by) {
      killed_by = ([ ]);
   }
   return killed_by;
}

void increment_kills() {
   kills++;
}

int query_kills() {
   return kills;
}

void killed_by(object who, int t) {
   if (!killed_by) {
      killed_by = ([ ]);
   }
   killed_by[t] = who;
}

int query_killed() {
   if (!killed_by) {
      killed_by = ([ ]);
   }
   return sizeof(map_indices(killed_by));
}

void halt_fight(void) {
   fighting = 0;
   targets = ( { } );
}

void receive_damage(object who, int dam) {
   this_object()->message("%^RED%^You took " + dam + " damage from " +
      who->query_id() + ".%^RESET%^");
   this_object()->decrease_hp(dam);
   if (this_object()->is_dead()) {
      this_object()->simple_action("$N $vfall to the ground...dead.");
      this_object()->message("You have died.");
      this_object()->halt_fight();
      this_object()->killed_by(who, time());
      this_object()->die();
      who->increment_kills();
   }
}

void damage_target(int dam, object who) {
   int target_hp;

   target_hp = who->query_hp();

   /* award expr for damage inflicted to target */
   if (dam > target_hp) {
      this_object()->increase_expr(target_hp);
   } else {
      this_object()->increase_expr(dam);
   }

   /* damage target */
   who->receive_damage(this_object(), dam);
}

int query_defense(void) {
   int me, i, max;
   object *armor;

   me = random(this_object()->query_skill("combat/defense") / 50);
   me += this_object()->query_statbonus("dex");
   armor = this_object()->query_equipment();

   max = sizeof(armor);
   for (i = 0; i < max; i++) {
      if (armor[i]->is_armor()) {
	 me += armor[i]->query_ac();
      }
   }

   armor = this_object()->query_wielded();
   max = sizeof(armor);
   for (i = 0; i < max; i++) {
      if (armor[i]->is_armor()) {
	 me += armor[i]->query_ac();
      }
   }

   return me;
}

int do_swing(int me) {
   int opponent, me_roll, opponent_roll;

   if (me < 3) {
      me = 3;
   }

   me_roll = random(me + 1);

   opponent = target->query_defense();
   opponent_roll = random(opponent + 1);

#ifdef DEBUG
      this_object()->message("Roll [%^RED%^" + me_roll + "%^RESET%^/%^GREEN%^" +
         me + "%^RESET%^  vs %^RED%^" + opponent_roll + "%^RESET%^/%^GREEN%^" +
         opponent + "%^RESET%^]");
#endif

   if (me_roll > opponent_roll) {
      return 1;
   }
   return 0;
}

object get_target(object targ) {
   int i, max;

   if (targ) {
      if (targ->is_dead()) {
	 targets -= ( { targ } );
	 if (sizeof(targets) == 0) {
	    fighting = 0;
         }
      } else if (targ->query_environment() ==
	 this_object()->query_environment()) {
	 fighting = FIGHTING_TIMEOUT;
	 return targ;
      }
   }
   max = sizeof(targets);
   for (i = 0; i < max; i++) {
      if (targets[i] && targets[i]->is_dead()) {
	 targets -= ( { targets[i] } );
         i--; max--; 	/* shorten up our array.... */
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
   fighting = fighting - 1;
   if (fighting < 1) {
      targets = ( { } );
      this_object()->message("You give up fighting your attacker.\n");
   }
   return nil;
}

void attack_with(string skill, object weapon, object target) {
   int me, tmp, damage;

   me = this_object()->query_end();
   if (me < ATTACK_COST) {
      this_object()->message("You are too tired to attack.\n");
      return;
   } else {
      this_object()->decrease_end(ATTACK_COST);
   }

   if (!weapon) {
      me = (this_object()->query_skill("combat/unarmed") / 50) +
	 this_object()->query_statbonus("str");
   } else {
      me = (this_object()->query_skill(weapon->query_weapon_skill()) / 50)
	 + this_object()->query_statbonus("str")
	 + weapon->query_hit_bonus();
   }
   if (do_swing(me) == 1) {
      if (!weapon) {
	 damage = random(3) + this_object()->query_statbonus("str");
	 tmp = this_object()->query_skill("combat/unarmed") +
	    this_object()->query_skill("combat/unarmed") / 2;
	 if (tmp <= target->query_skill("combat/defense")) {
	    this_object()->learn_skill(this_object()->query_hit_skill());
	    this_object()->message("Learn: hit_skill, " +
	       this_object()->query_skill("combat/unarmed"));
	 }

	 this_object()->targeted_action("$N $vhit $T.", target);

      } else {
	 damage = this_object()->query_statbonus("str") +
	    random((weapon->query_max_damage() -
	       weapon->query_min_damage())) + weapon->query_min_damage();
	 tmp = this_object()->query_skill(weapon->query_weapon_skill()) +
	    this_object()->query_skill(weapon->query_weapon_skill()) / 2;
	 if (tmp <= target->query_skill("combat/defense")) {
	    this_object()->learn_skill(weapon->query_weapon_skill());
	    this_object()->message("Learn: hit_skill, " +
	       this_object()->query_skill(weapon->query_weapon_skill()));
	 }

	 this_object()->targeted_action("$N " +
	    weapon->query_weapon_action() + " $T with a " +
	    weapon->query_id() + ".", target);
      }

      this_object()->damage_target(damage, target);
   } else {
      string miss;

      if (weapon) { 
         miss = weapon->query_weapon_miss();
      }

      if (!miss) {
         this_object()->targeted_action("$N $vmiss $T.", target);
      } else {
         this_object()->targeted_action("$N " + miss + " $T.", target);
      }

      if (!weapon) {
	 tmp = this_object()->query_skill("combat/unarmed") +
	    this_object()->query_skill("combat/unarmed") / 2;
      } else {
	 tmp = this_object()->query_skill(weapon->query_weapon_skill()) +
	    this_object()->query_skill(weapon->query_weapon_skill()) / 2;
      }
      if (target->query_skill("combat/defense") <= tmp) {
	 target->learn_skill("combat/defense");
	 target->message("Learn: defense, " + 
            this_object()->query_skill("combat/defense"));
      }
   }
}

void cast_spell(object target) {
   int damage;
   string message;

   damage = random(this_object()->query_spell_damage()) + 1;

   message = this_object()->query_spell_message();
   if (!message || (message == "")) {
      message = "Casts an unamed spell at $t.";
   }
   message =  replace_string(message, "$t", target->query_name());

   target->query_environment()->tell_room(this_object(), message);

   this_object()->damage_target(damage, target);
}

void do_fight(void) {
   int i, max, x, done;
   object *weapons;

   target = get_target(target);

   if (target) {
      if (!this_object()->is_player()) {
         x = this_object()->query_spell_chance();

         if (x && (random(100) <= x)) {
            cast_spell(target);
         }
      }

      weapons = this_object()->query_wielded();
      max = sizeof(weapons);

      if (max == 0) {
	 this_object()->attack_with("combat/unarmed", nil, target);
      } else {
	 for (i = 0; i < max; i++) {
	    if (!weapons[i]->query_offensive()) {
	       continue;
            }
	    this_object()->attack_with(weapons[i]->query_weapon_skill(), 
               weapons[i], target);
	 }
      }

#ifdef DEBUG
      /* Need to check target again, because target may have died. */
      if (target) {
         this_object()->message("%^CYAN%^HP[" + this_object()->query_hp() + 
            "/" + this_object()->query_max_hp() + "] Target HP[" + 
            target->query_hp() + "/" + target->query_max_hp()  + "]%^RESET%^");
         done = 1;
      }
#endif
      if (!done) {
         this_object()->message("%^CYAN%^HP[" + this_object()->query_hp() + 
            "/" + this_object()->query_max_hp() + "]%^RESET%^");
      }
   }
}

void attacked_by(object who) {
   if (!targets) {
      targets = ( { } );
   }
   targets += ( { who } );
   target = who;
   fighting = FIGHTING_TIMEOUT;
}

void attack(object who) {
   if (!targets) {
      targets = ( { } );
   }
   if (who->is_dead()) {
      return;
   }

   targets += ( { who } );
   fighting = FIGHTING_TIMEOUT;
   target = who;
   who->attacked_by(this_object());
   do_fight();
}
