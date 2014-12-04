#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Murky mists pocket dimension");
   set_long("You can 'leave' the pocket dimension. " +
      "Ideally it will return you to the room you " +
      "arrived from; if it is not found, then you " + "go to the base camp.");

   set_exits(([
      "north" : DIR + "/rooms/murky_mists/murky_mists_maze_start.c",
      "leave" : NOKICLIFFS_BASE_CAMP
   ]));
}
