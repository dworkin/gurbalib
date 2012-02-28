inherit RACE;

void create( void ) {
   ::create();

   set_race_short_desc( "Catfolk are very agile and sleak. ");
   set_race_long_desc( "Catfolk are misterious and keep too themselves.  " +
      "The other races are not quite sure where they originally came from.  " +
      "They just showed up one day and have been around ever since.  " +
      "Catfolk tend to be smaller that humans but are extremly dexterous." );

// XXX see dwarf code for why this is commented out...
//    set_skill("language/catfolk",100);
}
