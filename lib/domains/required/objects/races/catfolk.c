inherit "/std/race";

void create(void) {
   ::create();

   set_race_short_desc("Catfolk are very agile and sleek. ");
   set_race_long_desc("Catfolk are mysterious and keep too themselves.  " +
      "The other races are not quite sure where they originally came from.  " +
      "They just showed up one day and have been around ever since.  " +
      "Catfolk tend to be smaller that humans but are extremely dexterous.");

   set_language("catfolk");
   set_skill("language/catfolk", 100);
}

int has_darkvision(void) {
   return 1;
}

