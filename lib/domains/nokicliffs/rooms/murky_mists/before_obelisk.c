#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Murky mists hammock");
   set_long("You stand on what might be the driest patch " +
      "of terrain within the murky mist. This hammock, " +
      "however, provides no respite or comfort from the " +
      "evil energy of this place. And you still cannot see " +
      "very much.");

   set_exits(([
      "north" : DIR + "/rooms/murky_mists/obelisk.c",
      "east" : DIR + "/rooms/murky_mists/cross_road.c"
   ]));
}
