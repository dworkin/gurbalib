#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Escape");
   set_long("After walking down an endless mine shaft, you finally see the " +
      "light at the end of the tunnel.  There is a hole to the east.  " +
      "To the west the mine crawls deeper into the mountain.");

   set_exits(([
      "west" : DIR + "/rooms/mine/mineshaft.c",
   ]));
}

