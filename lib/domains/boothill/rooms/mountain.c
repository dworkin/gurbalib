#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Mountain");
   set_long("The path opens up into a clearing.  There is an old abandoned " +
      "mine to the east.  The mine doesn't look very safe.  West leads back " +
      "to town.");

   set_exits(([
      "east" : DIR + "/rooms/mine/mineent.c",
      "west" : DIR + "/rooms/mntpath.c",
   ]));
}
