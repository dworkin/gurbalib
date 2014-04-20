#include "../domain.h"

inherit "/std/sign";

void setup(void) {
   set_id("book");
   set_short("A book in a chain");
   set_long("There is a book hanging in a chain from the wall.\n" +
      "The title is: 'ADVENTURING'.\n");

   set_message("ADVENTURING.\n\n" +
      "On later years, it has become more and more complicated to " +
      "adventure and\ngather experience. This book was written to be a " +
      "guide for adventurers.\n\n" +
      "As everyone knows, the meaning of life is to gain experience " +
      "and raise\nyour level. This can be done here at the adventurers " +
      "guild, but a small\nfee is sometimes required if there is not " +
      "enough experience.\n\n" +
      "The best way to get experience is to exterminate bad monsters " +
      "that stroll\naround our city. Experience can also be gained by " +
      "killing players.\n\n" +
      "Your reputation will depend on how kind you are. If you kill " +
      "good players,\nyou will be regarded as evil. This is not good, " +
      "because other players\nwill stay out of your way, and gather " +
      "together and attack evil players.\n\n" +
      "The altogether top goal is to become wizard. All wizards will be " +
      "assigned\na castle, which they can rebuild any way they like.\n\n" +
      "Note: As this is a glorified version of real life, you better " +
      "get drunk\nif you are hurt. Then, you will heal faster. Never " +
      "trust privacy. Wizards\nhas eyes everywhere, which they use to " +
      "study usage of their castles etc.");
}
