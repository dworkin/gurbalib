/* Definition of the half-giant race */
inherit "/std/race";

void create(void) {
   ::create();

   set_race_short_desc("Half giants are a brutish crossbreed with humans");
   set_race_long_desc("Half giants. The crossbreed between man and giant. " +
      "The result is a\ncreature that looks human, except that it is twice " +
      "the size. Because of this,\nthey make excellent fighters, little " +
      "less so thinkers. Their size means they \nconsume food and drink at " +
      "four times the human rate, and they need specially \ntailored " +
      "equipment and armor. Despite all this, they're extremely strong, " +
      "and\nstories go of incidents where a frail half-giant has survived " +
      "where the\nstrongest humans have fallen.");
   set_language("grunt");
   set_skill("language/grunt", 100);
}
