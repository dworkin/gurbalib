#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A puzzling cave chamber in the Noki Cliffs.");
   set_long("The direction 'north' requires special treatment.");

   set_exits(([
    "north" : DIR + "/rooms/cliffs/cave/brain_room.c",
    "south" : DIR + "/rooms/cliffs/cave/bust_chamber.c"
   ]));
}

