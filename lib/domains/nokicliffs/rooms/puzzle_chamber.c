#include "../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A puzzling cave chamber in the Noki Cliffs.");
   set_long("The direction 'north' requires special treatment.");

   set_exits(([
    "north" : DIR + "/rooms/brain_room",
    "south" : DIR + "/rooms/bust_chamber"
   ]));
}

