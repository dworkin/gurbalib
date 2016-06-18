#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A cooridor in the Den of Chaos in a pocket dimension");
   set_long("You are standing in the " +
      "end of a cooridor in the Den of Chaos. " +
      "Like most of the places in the Den of Chaos the walls " +
      "reveal this cooridor was not deliberately constructed. " +
      "They are chaotic, meandering, wandering. There is nothing " +
      "but chaos here. " +
      "You can feel the chaos everywhere, indeed, but " +
      "it is quite strong to the east.");

   set_exits(([
      "east": DIR + "/rooms/den_of_chaos/lair.c",
      "south": DIR + "/rooms/den_of_chaos/cooridor_middle.c"
   ]));
}
