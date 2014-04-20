#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  A Trail leads into the forest to the east.  " +
      "The shore of Crescent Lake continues north and south.");

   add_exit("north", DIR + "/rooms/south/sshore2.c");
   add_exit("south", DIR + "/rooms/south/sshore4.c");
   add_exit("east", DIR + "/rooms/south/sforst11.c");
}
