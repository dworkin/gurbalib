#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level four");
   set_long("You are in the fourth level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "up from here.");

   set_exits(([
      "up" : DIR + "/rooms/doomspire/fifth_level.c",
      "south" : DIR + "/rooms/doomspire/fourth_level_start.c"
   ]));

   set_objects(DIR + "/monsters/doom_queen.c");
}
