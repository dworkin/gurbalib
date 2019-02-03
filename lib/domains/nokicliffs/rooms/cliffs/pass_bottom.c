#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A pass in the Noki Cliffs");
   set_long("You are standing at the bottom of a narrow " +
      "pass. The ledge you are on continues to the west " +
      "from here. You may also go further " +
      "east to get into the pass itself.");

   set_exits(([
      "east" : DIR + "/rooms/cliffs/pass.c",
      "west" : DIR + "/rooms/cliffs/ledge.c"
   ]));
}
