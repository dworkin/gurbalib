#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A crumbling stone monument");
   set_long("You are halfway up the hill.  A crumbling monument stands on " +
      "the side of the hill here.  On top of the hill, to the west, " +
      "stands the ruins of the tower of Arcanarton.  A path winds around " +
      "the hill to the north, and heads down to the sure of the island to " +
      "the south and east.");

   add_exit("north", DIR + "/rooms/south/sislnd14.c");
   add_exit("south", DIR + "/rooms/south/sislnd6.c");
   add_exit("east", DIR + "/rooms/south/sislnd5.c");
   add_exit("west", DIR + "/rooms/south/sislnd18.c");

   add_item("monument", "The monument is very old and is crumbling.  " +
      "Affixed to the side of the monument is a corroded old plaque.");

   add_item("plaque", "The plaque reads:\n" +
      "\tBEWARE ALL YE WHO READ THIS MESSAGE\n" +
      "\tBe it known, that on this day, the tower of the evil mage\n" +
      "\tArcanarton was destroyed in an attack by the combined forces\n" +
      "\tof all of the mages of the land of Lustria.\n" +
      "\tThe body of the mage Arcanarton was not found, and it is feared\n" +
      "\tthat his evil work in this world is not yet over.");
}
