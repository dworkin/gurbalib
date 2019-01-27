#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level two");
   set_long("You are in the second level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "down from here.");

   set_exits(([
      "down" : DIR + "/rooms/doomspire/doomspire_start.c",
      "north" : DIR + "/rooms/doomspire/second_level_end.c"
   ]));
}
