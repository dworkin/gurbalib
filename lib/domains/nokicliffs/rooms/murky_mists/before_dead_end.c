#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Murky mists deep swamp");
   set_long("Peering through the mysterious mists of the " +
      "swamp, the tangle of mangroves appear as horrible " +
      "twisted maws of demons and devils freshly spawned " +
      "from the fiery depths of Hell. You are up to your " +
      "knees in swamp and it only gets deeper to the north.");

   set_exits(([
      "north" : DIR + "/rooms/murky_mists/dead_end.c",
      "west" : DIR + "/rooms/murky_mists/cross_road.c"
   ]));
}
