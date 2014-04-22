#include "../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Oak grove in a pocket dimension.");
   set_long("");

   set_exits(([
    "north" : DIR + "/rooms/oak_grove_middle",
    "south" : DIR + "/rooms/summit"
   ]));
}

