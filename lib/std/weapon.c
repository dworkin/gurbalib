inherit ob "/std/object";
inherit "/std/modules/m_wieldable";

int max_damage, min_damage, weapon_class, hit_bonus;
string weapon_skill, weapon_miss, *weapon_action, *materials;

string *query_materials(void) {
   return materials;
}

void set_materials(string *new_materials) {
   materials = new_materials;
}

void add_material(string material) {
   if (!materials) {
      materials = ({ });
   }

   materials += ({ material });
   materials = uniq_array(materials);
}

int query_offensive(void) {
   return 1;
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
   return weapon_class;
}

void set_hit_bonus(int hb) {
   hit_bonus = hb;
}

int query_hit_bonus(void) {
   return hit_bonus;
}

void set_weapon_action(string verb) {
   if (!weapon_action) {
      weapon_action = ({ });
   }
   weapon_action = ({ verb });
}

void set_weapon_actions(string *verbs) {
   weapon_action = verbs;
}

void add_weapon_action(string verb) {
   if (!weapon_action) {
      weapon_action = ({ });
   }
   weapon_action += ({ verb });
}

string query_weapon_action(void) {
   if (!weapon_action) {
      weapon_action = ({ "bonk" });
      return "bonk";
   }
   return weapon_action[random(sizeof(weapon_action))];
}

string *query_weapon_actions(void) {
   if (!weapon_action) {
      weapon_action = ({ });
   }
   return weapon_action;
}

void set_weapon_miss(string verb) {
   weapon_miss = verb;
}

string query_weapon_miss(void) {
   return weapon_miss;
}

void set_weapon_skill(string skill) {
   weapon_skill = skill;
}

int is_standard_weapon_skill(string skill) {
   return !empty_str(skill) &&
      (skill == "small" || skill == "medium" || skill == "large");
}

string query_weapon_skill(void) {
   if (!weapon_skill) {
      return "combat/blunt/small";
   } else {
      return weapon_skill;
   }
}

int query_weapon_damage(void) {
   return (random(max_damage - min_damage) + min_damage);
}


void set_combat_stats(int min_d, int max_d, int hb) {
   set_min_damage(min_d);
   set_max_damage(max_d);
   set_hit_bonus(hb);
}

void create(void) {
   ob::create();
   set_gettable(1);
   max_damage = 1;
   min_damage = 1;
   hit_bonus = 0;
   weapon_class = 0;
   weapon_action = ({ "bonk" });
   materials = ({ });
}
