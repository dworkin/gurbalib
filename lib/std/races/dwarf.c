/* Definition of the human race */

inherit RACE;

void create( void ) 
{
  ::create();

   base_stat_minimum["str"] = 7;
   base_stat_minimum["con"] = 10;
   base_stat_minimum["dex"] = 3;
   base_stat_minimum["int"] = 3;
   base_stat_minimum["wis"] = 3;
   base_stat_minimum["cha"] = 3;

   base_stat_maximum["str"] = 18;
   base_stat_maximum["con"] = 18;
   base_stat_maximum["dex"] = 15;
   base_stat_maximum["int"] = 15;
   base_stat_maximum["wis"] = 18;
   base_stat_maximum["cha"] = 10;

   stat_mod["str"] = 1;
   stat_mod["con"] = 2;
   stat_mod["dex"] = -1;
   stat_mod["int"] = 0;
   stat_mod["wis"] = 0;
   stat_mod["cha"] = -2;

   set_race_short_desc( "Dwarves are stocky and strong, but lack magical talent." );
   set_race_long_desc( "Dwarves are natural hard workers. A lifetime of mining and smithing\nmake them strong and durable. They make excellent warriors, which is a career\nundertaken by many a dwarf. Dwarves cannot fully grasp the concept of magic,\ndwarven mages are long and far between. Instead most of them can resist magic\nto a certain degree. Dwarves get along nice with trolls and orcs, and they   \nshare the elves' distrust of one another. " );

}

