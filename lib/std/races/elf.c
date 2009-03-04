/* Definition of the human race */
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

   set_race_short_desc( "Elves are potent in magic and are fairly nimble. Not very strong." );
   set_race_long_desc( "Elves tend to live with nature. They are a noble and proud folk.  \nMagic is often their game, but they are commonly seen in other fields as well.\nBeing an elf means that you are not physically strong, but being as dextrous\nas you are means that you can still be a decent warrior. Of some reason long \nforgotten, elves do not get along with dwarves, trolls or orcs. They are\nconsidered crude, foul, and smelly." );
}
