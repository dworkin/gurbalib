#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Oak grove in a pocket dimension.");
   set_long("Here we can return to the summit by " +
		"going south.");

   set_exits(([
    "north" : DIR + "/rooms/oak_grove/oak_grove_middle.c",
    "south" : DIR + "/rooms/cliffs/summit.c"
   ]));
}

