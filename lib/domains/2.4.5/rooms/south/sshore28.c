#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  A Trail leads into the forest to the west.  " +
      "The shore of Crescent Lake continues east and southwest.");

   add_exit("east", DIR + "/rooms/south/sshore29.c");
   add_exit("west", DIR + "/rooms/south/sforst47.c");
   add_exit("southwest", DIR + "/rooms/south/sshore27.c");
}
