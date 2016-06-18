#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A rocky path in the high mountains");
   set_long("You are on a path going through the high " +
      "high mountains. To the east the Noki Cliffs loom " +
      "large. To the west is a mountain plateau.");

   set_exits(([
      "east" : DIR + "/rooms/cliffs/cliff_bottom.c",
      "west" : DIR + "/rooms/start.c"
   ]));
}
