static int heal_rate;
static int heal_amount;
static int heal_time;
int player_age;

#define YEAR 31536000
#define DAY 86400
#define HOUR 3600
#define MIN 60

void set_heal_rate(int rate) {
   heal_rate = rate;
}

int query_heal_rate(void) {
   return heal_rate;
}

void set_heal_step(int amt) {
   heal_amount = amt;
}

int query_heal_step(void) {
   return heal_amount;
}

void create(void) {
   EVENT_D->subscribe_event("heart_beat");
   heal_time = 0;
   heal_rate = 10;
   heal_amount = 2;
   if (!intp(player_age)) {
      player_age = 0;
   }
}

void event_heart_beat(void) {
   if (this_object()->query_hp() < 1) {
      if (this_object()->is_dead() && this_object()->is_player()) {
         heal_time++;
         if (heal_time > heal_rate) {
            heal_time = 0;
            write("You are dead.  You must pray to get your body back.\n");
         }
      } else {
         this_object()->die();
         return;
      }
   } else {
      heal_time++;
      if (heal_time > heal_rate) {
	 heal_time = 0;
	 if (this_object()->query_hp() < this_object()->query_max_hp()) {
	    this_object()->increase_hp(random(heal_amount) + 1);
         }
	 if (this_object()->query_mana() < this_object()->query_max_mana()) {
	    this_object()->increase_mana(random(heal_amount) + 1);
         }
	 if (this_object()->query_end() < this_object()->query_max_end()) {
	    this_object()->increase_end(random(2 * heal_amount) + 1);
         }
      }

      /* allow monsters to talk, cast spells etc... */
      if (!this_object()->is_player()) {
         this_object()->do_extra_actions();
      }

      /* Check here to see is we are in combat, if so, continue battle */
      if (this_object()->is_fighting() > 0) {
         this_object()->do_fight();
      } else {
         if (function_object("event_wander", this_object())) {
   	    call_other(this_object(), "event_wander");
         }
      }
   }

   /* A player ages when not idle */
   if (this_object()->is_player()) {
      if (this_object()->query_idle() < 60) {
	 player_age += HEART_BEAT_INTERVAL;
			if (query_mortal(this_object())) {
				TOP_SCORE_D->save(this_object());
			}
      }
   }
}

string query_age(void) {
   string ret, tmp;
   int years, days, hours, mins, secs;

   secs = player_age;
   ret = " ";
   while (secs > YEAR) {
      years += 1;
      secs -= YEAR;
   }
   while (secs > DAY) {
      days += 1;
      secs -= DAY;
   }
	while (secs > HOUR) {
		hours += 1;
		secs -= HOUR;
	}
   while (secs > MIN) {
      mins += 1;
      secs -= MIN;
   }

   if (years > 0) {
      if (years == 1) {
         tmp = " year ";
      } else {
         tmp = " years ";
      }
      ret += years + tmp;
   }
   if (days > 0) {
      if (days == 1) {
         tmp = " day ";
      } else {
         tmp = " days ";
      }
      ret += days + tmp;
   }
   if (hours > 0) {
      if (hours == 1) {
         tmp = " hr ";
      } else {
         tmp = " hrs ";
      }
      ret += hours + tmp;
   }
   if (mins > 0) {
      if (mins == 1) {
         tmp = " min ";
      } else {
         tmp = " mins ";
      }
      ret += mins + tmp;
   }
   if (secs > 0) {
      if (secs == 1) {
         tmp = " sec ";
      } else {
         tmp = " secs ";
      }
      ret += secs + tmp;
   }

   return ret;
}

int query_age_in_seconds(void) {
   return player_age;
}

void die(void) {
   object killer, obj, *inv;
   int i;

	killer = this_object()->query_killer();
	if (killer) {
		killer->message("%^BOLD%^%^CYAN%^You killed " +
			this_object()->query_Name() + ".%^RESET%^");
	}
   this_object()->simple_action("$N $vfall to the ground...dead.");

   obj = clone_object(DOMAINS_DIR + "/required/objects/corpse");

   inv = this_object()->query_inventory();
   for(i = sizeof(inv) - 1; i>=0; i--) {
      if(inv[i]->query_worn()) {
         this_object()->do_remove(inv[i]);
      }
      if(inv[i]->query_wielded()) {
         this_object()->do_unwield(inv[i]);
      }
      inv[i]->move(obj);
   }

   obj->set_name(this_object()->query_name());
   obj->move(this_object()->query_environment());

   if (this_object()->is_player()) {
      this_object()->set_dead(1);
      this_object()->move(VOID);
      this_object()->message("You have died.");
      this_object()->clear_money();
   } else {
		if (this_object()<-"/std/monster") {
			this_object()->monster_died();
		}
      EVENT_D->unsubscribe_event("heart_beat");
      this_object()->destruct();
   }
}
