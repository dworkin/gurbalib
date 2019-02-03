#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level three");
   set_long("You are in the third level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "down from here.");

   set_exits(([
      "down" : DIR + "/rooms/doomspire/second_level_end.c",
      "south" : DIR + "/rooms/doomspire/third_level_end.c"
   ]));
}
