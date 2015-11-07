/* Definition of the elf race */
inherit "/std/race";

void create(void) {
   ::create();

   set_race_short_desc("Elves are potent in magic and are fairly nimble. " +
      "Not very strong.");
   set_race_long_desc("Elves tend to live with nature. They are a noble " +
      "and proud folk.\nMagic is often their game, but they are commonly " +
      "seen in other fields as well.\nBeing an elf means that you are not " +
      "physically strong, but being as dextrous\nas you are means that you " +
      "can still be a decent warrior. Of some reason long \nforgotten, " +
      "elves do not get along with dwarves, trolls or orcs. They are\n" +
      "considered crude, foul, and smelly.");
   set_language("elvish");
   set_skill("language/elvish", 100);
}

int has_darkvision(void) {
   return 1;
}
