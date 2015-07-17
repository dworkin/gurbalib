#include <type.h>

inherit con "/std/container";
inherit bod "/std/body";
inherit "/std/body/skills";

inherit "/std/modules/m_messages";
inherit "/std/modules/m_actions";

static int aggressive, spell_chance, spell_damage;
static string spell_message;

void create(void) {
   int x;

   con::create();
   bod::create();
   set_gettable(0);

   x = random(2) + 1;
   switch (x) {
      case 1:
         set_gender("male");
         break;
      case 2:
         set_gender("female");
         break;
      default:
         set_gender("unkown");
         break;
   }
}

void set_race(string str, varargs int is_new_player) {
   ::set_race(str, 1);
}

int is_attackable(void) {
   return 1;
}

void set_wearing(mixed obj) {
   object armor;

   if (!obj) {
      return;
   }

   if (typeof(obj) == T_STRING) {
      /* We've got to compile our own copy */
      armor = clone_object(obj);
      if (armor) {
         armor->setup();
         armor->move(this_object());
         if (!query_slot(armor->query_slot())) {
            do_wear(armor);
         }
      }
   } else {
      obj->move(this_object());
      if (!query_slot(obj->query_slot())) {
         do_wear(obj);
      }
   }
}

void set_wielding(mixed obj) {
   object weapon;

   if (!obj) {
      return;
   }

   if (typeof(obj) == T_STRING) {
      /* We've got to compile our own copy */
      weapon = clone_object(obj);
      if (weapon) {
         weapon->setup();
         weapon->move(this_object());
         do_wield(weapon);
      }
   } else {
      obj->move(this_object());
      do_wield(obj);
   }
}

void message(string str, varargs int chat_flag) {
   if (is_possessed()) {
      query_possessor()->message("%^RED%^$%^RESET%^" + str, chat_flag);
   }
}

void message_orig(string str) {
   if (is_possessed()) {
      query_possessor()->message_orig("%^RED%^$%^RESET%^" + str);
   }
}

void set_aggressive(int x) {
   aggressive = x;
}

int query_aggressive(void) {
   return aggressive;
}

int set_level(int x) {
   level = x;
   x = x * 6;
   set_max_hp(x);
   set_hp(x);
   set_max_mana(x);
   set_mana(x);
   set_max_end(x * 2);
   set_end(x * 2);
   return 1;
}

int query_level(void) {
   return level;
}

/* Simple spell system for monsters */

int set_spell_chance(int x) {
   if (x < 0) {
      x = 0;
   }
   if (x > 100) {
      x = 100;
   }
   spell_chance = x;
}

int set_spell_damage(int x) {
   spell_damage = x;
}

int set_spell_message(string str) {
   spell_message = str;
}

int query_spell_chance(void) {
   return spell_chance;
}

int query_spell_damage(void) {
   return spell_damage;
}

string query_spell_message(void) {
   return spell_message;
}

void monster_died(void) {
}

void equip_monster(string *arms, varargs int repeats_ok) {
   object obj, p;
   int i, dim;

   for (i = 0, dim = sizeof(arms); i < dim; i++) {
      obj = clone_object(arms[i]);
      obj->setup();
      p = present(obj->query_id());
      if (!p || repeats_ok) { 
         obj->move(this_object());
         if (obj->is_wieldable()) {
            do_wield(obj);
         } else if (obj->is_wearable()) {
            do_wear(obj);
         }
      } else if (p) {
         if (p->is_wieldable()) {
            do_wield(p);
         } else if (p->is_wearable()) {
            do_wear(p);
         }
      }
   }
}

void add_coins(string type, int amt) {
   object coins;

   if (present("coins")) {
      return;
   }
   if (amt < 1) {
      amt = 1;
   }
   if (MONEY_D->is_currency(type)) {
      coins = clone_object("/domains/required/objects/coin.c");
      coins->set_currency(type);
      coins->set_amount(amt);
      coins->move(this_object());
   }
}

