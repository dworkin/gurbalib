#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Halfway up the hill on the Isle of the Magi");
   set_long("An old, disused well stands here.  The roof having fallen in " +
      "from neglect.  On top of the hill, to the east, " +
      "stands the ruins of the tower of Arcanarton.  Paths wind down to " +
      "the shore of the island to the north and south.  Down on the shore " +
      "to the west is a small grove.  The well has a ladder running down " +
      "into it.");

   add_exit("north", DIR + "/rooms/south/sislnd12.c");
   add_exit("south", DIR + "/rooms/south/sislnd8.c");
   add_exit("east", DIR + "/rooms/south/sislnd18.c");
   add_exit("west", DIR + "/rooms/south/sislnd9.c");
   add_exit("down", DIR + "/rooms/south/lair.c");
}
