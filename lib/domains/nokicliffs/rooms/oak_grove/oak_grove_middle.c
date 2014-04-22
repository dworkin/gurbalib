#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Oak grove pocket dimension.");
   set_long("Continue north to the oak. " +
    "Add exits here to extend the grove or domain in general.");

   set_exits(([
    "north" : DIR + "/rooms/oak_grove/oak_grove_clearing.c",
    "south" : DIR + "/rooms/oak_grove/oak_grove_start.c"
   ]));
}

