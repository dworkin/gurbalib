#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A clearing in the oak grove pocket dimension");
   set_long("The long description depends from the status " +
      "of the quest.");

   set_exits(([
      "south" : DIR + "/rooms/oak_grove/oak_grove_middle.c"
   ]));
}

