#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Hallway in the Abbey of Law.");
   set_long("You are in a long hallway in the Abbey of Law. " +
      "You are surrounded by dorm rooms but the doors are " +
      "sealed shut in silent vigil never to be opened again.");

   set_exits(([
      "east" : DIR + "/rooms/abbey_of_law/outside_chapel.c",
      "west" : DIR + "/rooms/abbey_of_law/lobby.c"
   ]));
}
