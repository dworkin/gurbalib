#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  Trails lead into the forest to the north and south.  " +
      "The shore of Crescent Lake continues northeast and southeast.");

   add_exit("north", DIR + "/rooms/south/sforst30.c");
   add_exit("south", DIR + "/rooms/south/sforst31.c");
   add_exit("northeast", DIR + "/rooms/south/sshore20.c");
   add_exit("southeast", DIR + "/rooms/south/sshore18.c");
}
