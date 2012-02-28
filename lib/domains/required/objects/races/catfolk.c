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

  /* Note : The racial MAX stats are WITHOUT the bonus. */
   base_stat_maximum = ([ ]);
   base_stat_maximum["str"] = 33;
   base_stat_maximum["con"] = 33;
   base_stat_maximum["dex"] = 33;
   base_stat_maximum["int"] = 33;
   base_stat_maximum["wis"] = 33;
   base_stat_maximum["cha"] = 33;

   set_race_short_desc( "Catfolk are very agile and sleak. ");
   set_race_long_desc( "Catfolk are misterious and keep too themselves.  " +
      "The other races are not quite sure where they originally came from.  " +
      "They just showed up one day and have been around ever since.  " +
      "Catfolk tend to be smaller that humans but are extremly dexterous." );

// XXX see dwarf code for why this is commented out...
//    set_skill("language/catfolk",100);
}
