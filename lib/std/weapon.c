inherit ob OBJECT;
inherit M_WIELDABLE;

int max_damage;
int min_damage;
int weapon_class;
int hit_bonus;
string weapon_skill;
string weapon_action;

void create(void) {
   ob::create();
   set_gettable(1);
   max_damage = 1;
   min_damage = 1;
   hit_bonus = 0;
   weapon_class = 0;
   weapon_action = "bonk";
}

int query_offensive(void) {
   return (1);
}

void set_max_damage(int dam) {
   max_damage = dam;
}

void set_min_damage(int dam) {
   min_damage = dam;
}

int query_max_damage(void) {
   return max_damage;
}

int query_min_damage(void) {
   return min_damage;
}

void set_weapon_class(int class) {
   weapon_class = class;
}

int query_weapon_class(void) {
   return (weapon_class);
}

void set_hit_bonus(int hb) {
   hit_bonus = hb;
}

int query_hit_bonus(void) {
   return (hit_bonus);
}

void set_weapon_action(string verb) {
   weapon_action = verb;
}

string query_weapon_action(void) {
   return (weapon_action);
}

void set_weapon_skill(string skill) {
   weapon_skill = skill;
}

string query_weapon_skill(void) {
   if (!weapon_skill) {
      return "combat/impact/small";
   } else {
      return weapon_skill;
   }
}

int query_weapon_damage(void) {
   return (random(max_damage - min_damage) + min_damage);
}
