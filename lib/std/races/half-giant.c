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
   set_race_long_desc( "Half giants. The crossbreed between man and giant. The result is a\ncreature that looks human, except that it is twice the size. Because of this,\nthey make excellent fighters, little less so thinkers. Their size means they \nconsume food and drink at four times the human rate, and they need specially \ntailored equipment and armor. Despite all this, they're extremely strong, and\nstories go of incidents where a frail half-giant has survived where the\nstrongest humans have fallen." );

}
