#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level one");
   set_long("You are in the first level of the Doomspire. " +
      "Go up the spiral staircase to experience your doom. " +
      "You can leave the pocket dimension. " +
      "Ideally it will return you to the room you " +
      "arrived from; if it is not found, then you " +
      "go to the base camp.");

   set_exits(([
      "up" : DIR + "/rooms/doomspire/second_level_start.c",
      "leave" : NOKICLIFFS_BASE_CAMP
   ]));
}
