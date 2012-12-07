#include <type.h>

inherit con CONTAINER;
inherit bod BODY;
inherit "/std/body/skills";

inherit M_MESSAGES;

string living_name;
static object possessor;
static int aggressive;

void create(void) {
   int x;

   con::create();
   bod::create();
   set_gettable(0);
   living_name = nil;

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

int is_player(void) {
   return 0;
}

int is_living(void) {
   return 1;
}

int is_possessed(void) {
   if (possessor)
      return 1;
   return 0;
}

void set_possessor(object ob) {
   possessor = ob;
}

object query_possessor(void) {
   return possessor;
}

int is_attackable(void) {
   return 1;
}

void set_name(string name) {
   living_name = name;
   set_id(name);
}

string query_name(void) {
   return (living_name);
}

void set_wearing(mixed obj) {
   object armor;

   if (!obj)
      return;

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
   if (is_possessed())
      query_possessor()->message("%^RED%^$%^RESET%^" + str, chat_flag);
}

void message_orig(string str) {
   if (is_possessed())
      query_possessor()->message_orig("%^RED%^$%^RESET%^" + str);
}

void set_aggressive(int x) {
   aggressive = x;
}

int query_aggressive() {
   return aggressive;
}

/* XXX Need to expand this... :) */
int set_level(int x) {
   x = x * 6;
   set_max_hp(x);
   set_hp(x);
   set_max_mana(x);
   set_mana(x);
   set_max_end(x * 2);
   set_end(x * 2);
/*   set_ac(x /4); */
   return 1;
}
