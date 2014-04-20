#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  Trails lead into the forest to the north and east.  " +
      "The shore of Crescent Lake continues south and northwest.");

   add_exit("north", DIR + "/rooms/south/sforst8.c");
   add_exit("south", DIR + "/rooms/south/sshore2.c");
   add_exit("east", DIR + "/rooms/south/sforst9.c");
   add_exit("northwest", DIR + "/rooms/south/sshore30.c");
}
