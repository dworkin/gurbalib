/* Definition of the human race */

inherit RACE;

void create( void ) {
   ::create();
   base_stat_minimum = ([ ]);
   base_stat_minimum["str"] = 3;
   base_stat_minimum["con"] = 3;
   base_stat_minimum["dex"] = 3;
   base_stat_minimum["int"] = 3;
   base_stat_minimum["wis"] = 3;
   base_stat_minimum["cha"] = 3;

   base_stat_maximum = ([ ]);
   base_stat_maximum["str"] = 33;
   base_stat_maximum["con"] = 33;
   base_stat_maximum["dex"] = 33;
   base_stat_maximum["int"] = 33;
   base_stat_maximum["wis"] = 33;
   base_stat_maximum["cha"] = 33;

   set_race_short_desc( "Humans are cursed with beeing average in all aspects." );
   set_race_long_desc( "Humans are predominant in the lands. They, as a race, have most of\nthe power in the realm. Since they are so, all the other races are compared \n to them. They get along with all the other races fairly well, and a human has\na wide range of adventuring options available to him or her. The downside is \nthat they do not excel in any particular fields." );
}
