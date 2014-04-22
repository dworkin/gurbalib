#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("The base camp of the summit of the Noki Cliffs.");
   set_long("You have reached a suitable base camp for "+
		"summitting the Noki Cliffs. In order to proceed you " +
		"will need some climbing gear.");

   set_exits(([
	 "up" : DIR + "/rooms/cliffs/summit.c",
	 "down" : DIR + "/rooms/cliffs/cave/cave_start.c"
   ]));
}

