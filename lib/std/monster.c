#include <type.h>

inherit con "/std/container";
inherit bod "/std/body";
inherit "/std/body/skills";

inherit "/std/modules/m_messages";
inherit "/std/modules/m_actions";

static int aggressive;
int spell_chance, spell_damage;
string spell_message;

void create(void) {
   int x;

   con::create();
   bod::create();
   set_gettable(0);

   x = random(2) + 1;
   switch (x) {
      case 1:
	 set_gender("male");
      case 2:
	 set_gender("female");
      default:
	 set_gender("unkown");
   }
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

   if (!obj)
      return;

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

int query_aggressive() {
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

int query_level() {
   return level;
}

/* Simple spell system for monsters */

/* Takes a number 0-100 */
int set_spell_chance(int x) {
   spell_chance = x;
}

int set_spell_damage(int x) {
   spell_damage = x;
}

int set_spell_message(string str) {
   spell_message = str;
}

int query_spell_chance() {
   return spell_chance;
}

int query_spell_damage() {
   return spell_damage;
}

string query_spell_message() {
   return spell_message;
}
