#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A passage in the Den of Chaos in a pocket dimension");
   set_long("You are standing in a passage in the Den of Chaos. " +
      "The passage goes north and south from here, both leading " +
      "deeper in the chaos that is pervasive here. The entrance " +
      "(or exit) to the Den lies to the west.");

   set_exits(([
      "west": DIR + "/rooms/den_of_chaos/den_of_chaos_start.c",
      "north": DIR + "/rooms/den_of_chaos/cooridor_start.c",
      "south": DIR + "/rooms/den_of_chaos/slope_start.c"
   ]));
}
