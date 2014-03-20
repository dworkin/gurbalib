#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  Trails lead into the forest to the south and west.  " +
      "The shore of Crescent Lake continues northwest and southeast.");

   add_exit("north", DIR + "/rooms/south/sforst49.c");
   add_exit("east", DIR + "/rooms/south/sforst46.c");
   add_exit("northwest", DIR + "/rooms/south/sshore24.c");
   add_exit("southeast", DIR + "/rooms/south/sshore26.c");
}
