static object *targets;
static int fighting;
static object target;

#define FIGHTING_TIMEOUT 300
/* Ammount of Endurance required to Attack */
#define ATTACK_COST 5

void create(void) {
   targets = ( { } );
   fighting = 0;
}

int is_fighting(void) {
   return (fighting);
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
      this_object()->die();
   }
}

void damage_target(int dam, object who) {
   int target_hp;

   target_hp = this_object()->query_hp();

   /* award expr for damage inflicted to target */
   if (dam > target_hp) {
      who->increase_expr(target_hp);
   } else {
      who->increase_expr(dam);
   }

   /* damage target */
   this_object()->receive_damage(who, dam);
}

int query_defense(void) {
   int me, i;
   object *armor;

   me = random(this_object()->query_skill("combat/defense") / 50);
   me += this_object()->query_statbonus("dex");
   armor = this_object()->query_equipment();
   for (i = 0; i < sizeof(armor); i++) {
      if (armor[i]->is_armor()) {
	 me += armor[i]->query_ac();
      }
   }

   armor = this_object()->query_wielded();
   for (i = 0; i < sizeof(armor); i++) {
      if (armor[i]->is_armor()) {
	 me += armor[i]->query_ac();
      }
   }

   return me;
}

int do_swing(int me) {
   int opponent, me_roll, opponent_roll;

   if (me < 3) me = 3;

   me_roll = random(me + 1);

   opponent = target->query_defense();
   opponent_roll = random(opponent + 1);

/* XXX This is temporary...  */
   this_object()->message("Roll [%^RED%^" + me_roll + "%^RESET%^/%^GREEN%^" +
      me + "%^RESET%^  vs %^RED%^" + opponent_roll + "%^RESET%^/%^GREEN%^" +
      opponent + "%^RESET%^]");

   if (me_roll > opponent_roll)
      return 1;
   return 0;
}

object get_target(object targ) {
   int i, max;

   if (targ) {
      if (targ->is_dead()) {
	 targets -= ( { targ } );
	 if (sizeof(targets) == 0)
	    fighting = 0;
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

	 this_object()->targetted_action("$N $vhit $T.", target);

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

	 this_object()->targetted_action("$N " +
	    weapon->query_weapon_action() + " $T with a " +
	    weapon->query_id() + ".", target);
      }

      target->damage_target(damage, this_object());
   } else {
      string miss;

      if (miss) {
         this_object()->targetted_action("$N $vmiss $T.", target);
      } else {
         this_object()->targetted_action(miss, target);
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

void do_fight(void) {
   int i;
   object *weapons;

   target = get_target(target);

   if (target) {
      weapons = this_object()->query_wielded();

      if (sizeof(weapons) == 0) {
	 this_object()->attack_with("combat/unarmed", nil, target);
      } else {
	 for (i = 0; i < sizeof(weapons); i++) {
	    if (!weapons[i]->query_offensive())
	       continue;
	    this_object()->attack_with(weapons[i]->query_weapon_skill(), 
               weapons[i], target);
	 }
      }

      this_object()->message("%^CYAN%^HP[" + this_object()->query_hp() + "/" +
/* XXX	 this_object()->query_max_hp() + "]%^RESET%^"); */
	 this_object()->query_max_hp() + "] Target HP[" + 
         target->query_hp() + "/" + target->query_max_hp()  + "]%^RESET%^");
   }
}

void attacked_by(object who) {
   if (!targets)
      targets = ( { } );
   targets += ( { who } );
   target = who;
   fighting = FIGHTING_TIMEOUT;
}

void attack(object who) {
   if (!targets)
      targets = ( { } );
   if (who->is_dead()) {
      return;
   }

   targets += ( { who } );
   fighting = FIGHTING_TIMEOUT;
   target = who;
   who->attacked_by(this_object());
   do_fight();
}
