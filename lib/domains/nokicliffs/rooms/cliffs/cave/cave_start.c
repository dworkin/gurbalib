#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A cave entrance in the Noki Cliffs.");
   set_long("");

   set_exits(([
	 "up" : DIR + "/rooms/cliffs/base_camp.c",
    "north" : DIR + "/rooms/cliffs/cave/bust_chamber.c",
    "east" : DIR + "/rooms/cliffs/ledge.c"
   ]));
}

