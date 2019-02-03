#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level four");
   set_long("You are in the fourth level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "down from here.");

   set_exits(([
      "down" : DIR + "/rooms/doomspire/third_level_end.c",
      "north" : DIR + "/rooms/doomspire/fourth_level_end.c"
   ]));
}
