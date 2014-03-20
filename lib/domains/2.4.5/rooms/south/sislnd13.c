#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Halfway up the hill on the Isle of the Magi");
   set_long("You are halfway up the hill.  On top of the hill, to the " +
      "south, stands the ruins of the tower of Arcanarton.  The bridge to " +
      "the mainland stands at the base of the hill to the north.  A path " +
      "heads around the hill to the east, and down the hill to the shore of " +
      "the island to the west.");

   add_exit("north", DIR + "/rooms/south/sislnd1.c");
   add_exit("south", DIR + "/rooms/south/sislnd18.c");
   add_exit("east", DIR + "/rooms/south/sislnd14.c");
   add_exit("west", DIR + "/rooms/south/sislnd12.c");
}
