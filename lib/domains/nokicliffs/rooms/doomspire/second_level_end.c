#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level two");
   set_long("You are in the second level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "up from here.");

   set_exits(([
      "up" : DIR + "/rooms/doomspire/third_level_start.c",
      "south" : DIR + "/rooms/doomspire/second_level_start.c"
   ]));

   set_objects(DIR + "/monsters/animated_skeleton.c");
}
