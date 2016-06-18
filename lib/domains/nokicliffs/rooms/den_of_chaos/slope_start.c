#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A slope in the Den of Chaos in a pocket dimension");
   set_long("You are standing on a slope in the Den of Chaos. " +
      "The slope both inclines and declines to the east from here. " +
      "You cannot say which is actually the case; you are thoroughly " +
      "convinced that it is both at the very same time although that " +
      "seems impossible. Also a passage wanders chaotically to the north " +
      "from here.");

   set_exits(([
      "north": DIR + "/rooms/den_of_chaos/passage.c",
      "east": DIR + "/rooms/den_of_chaos/slope_end.c"
   ]));
}
