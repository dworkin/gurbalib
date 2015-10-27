mapping races;
string *names;
mapping monster_races;
string *monster_names;

void create(void) {
   mixed *list;
   object race;
   int i, sz;

   races = ([]);

   list = get_dir(RACE_DIR + "/*.c");
   names = list[0];

   sz = sizeof(names);
   for (i = 0; i < sz; i++) {
      names[i] = names[i][..(strlen(names[i]) - 3)];
      race = clone_object(RACE_DIR + "/" + names[i]);
      races[names[i]] = race;
   }

   monster_races = ([]);
   list = get_dir(RACE_DIR + "/monsters/*.c");
   monster_names = list[0];

   sz = sizeof(monster_names);
   for (i = 0; i < sz; i++) {
      monster_names[i] = monster_names[i][..(strlen(monster_names[i]) - 3)];
      race = clone_object(RACE_DIR + "/monsters/" + monster_names[i]);
      monster_races[monster_names[i]] = race;
   }
}

string *query_races(void) {
   return names;
}

string *query_monster_races(void) {
   return monster_names;
}

int is_monster_race(string race) {
   return member_array(race, map_indices(monster_races)) != -1;
}

int is_race(string race) {
   return member_array(race, map_indices(races)) != -1;
}

object query_race_object(string race) {

   if (!races[race]) {
      return monster_races[race];
   }

   return races[race];
}

string query_race_short(string race) {
   if (!races[race]) {
      return monster_races[race]->query_race_short_desc();
   }
   return races[race]->query_race_short_desc();
}

string query_race_long(string race) {
   if (!races[race]) {
      return monster_races[race]->query_race_long_desc();
   }
   return races[race]->query_race_long_desc();
}
