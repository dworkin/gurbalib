/* Definition of the rat race */

inherit MONSTER_RACE;

void create( void ) 
{
   base_stat_minimum = ([ ]);
   base_stat_minimum["str"] = 2;
   base_stat_minimum["con"] = 2;
   base_stat_minimum["dex"] = 2;
   base_stat_minimum["int"] = 2;
   base_stat_minimum["wis"] = 2;
   base_stat_minimum["cha"] = 2;

   base_stat_maximum = ([ ]);
   base_stat_maximum["str"] = 10;
   base_stat_maximum["con"] = 10;
   base_stat_maximum["dex"] = 10;
   base_stat_maximum["int"] = 10;
   base_stat_maximum["wis"] = 10;
   base_stat_maximum["cha"] = 10;

   set_race_short_desc( "Rodents are small and foul smelling." );
   set_race_long_desc( "Stench! Disease! Germs! Plague!" );
}

