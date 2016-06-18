#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Oak grove in a pocket dimension");
   set_long("The oak grove is one of the oldest realms " +
      "of the multiverse. Only those with the mark of " +
      "the Ancient One are allowed to explore it in any " +
      "depth.");

   set_exits(([
      "north" : DIR + "/rooms/oak_grove/oak_grove_middle.c",
      "leave" : NOKICLIFFS_BASE_CAMP
   ]));
}
