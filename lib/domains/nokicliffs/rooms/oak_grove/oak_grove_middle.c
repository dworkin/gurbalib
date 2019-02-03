#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Oak grove pocket dimension");
   set_long("Continue north to the great oak. " +
            "Here the sun is warm, the breeze is " +
            "soothing, and everything seems to be " +
            "just fine. This is a happy place.");

   set_exits(([
      "north" : DIR + "/rooms/oak_grove/oak_grove_clearing.c",
      "south" : DIR + "/rooms/oak_grove/oak_grove_start.c"
   ]));

   set_objects(
      NOKICLIFFS_MONSTERS_DIR + "/faerie.c",
      NOKICLIFFS_MONSTERS_DIR + "/pixie.c"
   );
}

