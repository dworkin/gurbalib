/* Definition of the dwarf race */
/* Note : The racial MAX stats are WITHOUT the bonus. */

inherit RACE;

void create( void ) {
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

   set_race_short_desc( "Gnomes are the brainy brothers of the dwarves.." );
   set_race_long_desc( "Gnomes are a strange folk. Most humans would call them freaks. Always\ntoying with inventions, strange devices, or mysterious summonings, rarely \na day goes by in a gnome community without some sort of explosion or monster \non the loose. Yet they keep continuing. Gnomes seem obsessed with investigating\nand finding out of things they come across - often with disastrous results." );

}
