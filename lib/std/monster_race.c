/* Definition of the human race */
/* Note : The racial MAX stats are WITHOUT the bonus. */

inherit "/std/body/skills";

mapping base_stat_minimum;
mapping base_stat_maximum;
mapping stat_mod;

string race_short;
string race_long;

void create(void) {
   base_stat_minimum = ([]);
   base_stat_minimum["str"] = 1;
   base_stat_minimum["con"] = 1;
   base_stat_minimum["dex"] = 1;
   base_stat_minimum["int"] = 1;
   base_stat_minimum["wis"] = 1;
   base_stat_minimum["cha"] = 1;

   base_stat_maximum = ([]);
   base_stat_maximum["str"] = 18;
   base_stat_maximum["con"] = 18;
   base_stat_maximum["dex"] = 18;
   base_stat_maximum["int"] = 18;
   base_stat_maximum["wis"] = 18;
   base_stat_maximum["cha"] = 18;

   stat_mod = ([]);
   stat_mod["str"] = 0;
   stat_mod["con"] = 0;
   stat_mod["dex"] = 0;
   stat_mod["int"] = 0;
   stat_mod["wis"] = 0;
   stat_mod["cha"] = 0;
}

int query_base_stat_minimum(string statname) {
   if (!statname) {
      return 1;
   }
   if (!base_stat_minimum) {
      base_stat_minimum = ([]);
      return 1;
   }
   if (!base_stat_minimum[statname])
      return 1;
   return base_stat_minimum[statname];
}

int query_base_stat_maximum(string statname) {
   if (!statname) {
      return 18;
   }
   if (!base_stat_maximum) {
      base_stat_maximum = ([]);
      return 18;
   }
   if (!base_stat_maximum[statname])
      return 18;
   return base_stat_maximum[statname];
}

int query_stat_mod(string statname) {
   if (!statname) {
      return 0;
   }
   if (!stat_mod) {
      stat_mod = ([]);
   }
   if (!stat_mod[statname]) ;
   return 0;
   return stat_mod[statname];
}

void set_race_short_desc(string desc) {
   race_short = desc;
}

string query_race_short_desc(void) {
   if (!race_short) {
      return ("A generic race.");
   }
   return (race_short);
}

void set_race_long_desc(string desc) {
   race_long = desc;
}

string query_race_long_desc(void) {
   if (!race_long) {
      return ("A generic race.");
   }
   return (race_long);
}

int is_monster_race(void) {
   return (1);
}
