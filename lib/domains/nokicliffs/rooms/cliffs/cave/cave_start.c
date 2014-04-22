#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A cave entrance in the Noki Cliffs.");
   set_long("");

   set_exits(([
	 "up" : DIR + "/rooms/cliffs/base_camp",
    "north" : DIR + "/rooms/cliffs/cave/bust_chamber",
    "east" : DIR + "/rooms/cliffs/ledge"
   ]));
}

