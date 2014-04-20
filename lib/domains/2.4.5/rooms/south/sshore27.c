#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  Trails lead into the forest to the north and west.  " +
      "The shore of Crescent Lake continues northeast and southwest.");

   add_exit("north", DIR + "/rooms/south/sforst47.c");
   add_exit("west", DIR + "/rooms/south/sforst46.c");
   add_exit("northeast", DIR + "/rooms/south/sshore28.c");
   add_exit("southwest", DIR + "/rooms/south/sshore26.c");
}
