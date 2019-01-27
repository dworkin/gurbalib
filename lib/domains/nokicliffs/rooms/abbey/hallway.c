#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Hallway in the Abbey.");
   set_long("You are in a long hallway in the Abbey. " +
      "You are surrounded by dorm rooms but the doors are " +
      "sealed shut in silent vigil never to be opened again.");

   set_exits(([
      "east" : DIR + "/rooms/abbey/outside_chapel.c",
      "west" : DIR + "/rooms/abbey/lobby.c"
   ]));
}
