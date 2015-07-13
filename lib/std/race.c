inherit "/std/monster_race";

string language;

int is_monster_race(void) {
   return 0;
}

string query_language(void) {
   return language;
}

string set_language(string str) {
   language = str;
}

int has_darkvision(void) {
   return 0;
}

void create(void) {
   ::create();

   base_stat_minimum["str"] = 3;
   base_stat_minimum["con"] = 3;
   base_stat_minimum["dex"] = 3;
   base_stat_minimum["int"] = 3;
   base_stat_minimum["wis"] = 3;
   base_stat_minimum["cha"] = 3;

   base_stat_maximum["str"] = 33;
   base_stat_maximum["con"] = 33;
   base_stat_maximum["dex"] = 33;
   base_stat_maximum["int"] = 33;
   base_stat_maximum["wis"] = 33;
   base_stat_maximum["cha"] = 33;
}
