#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Murky mists cross road");
   set_long("You are deep within the murky mists. It is very " +
      "swampy here, ankle deep in murky swamp water. " +
      "The entire area shrouded in a mysterious mist. " +
      "You experience great difficulty seeing where to go. " +
      "The paths of least resistance go east and west from " +
      "here.");

   set_exits(([
      "south" : DIR + "/rooms/murky_mists/murky_mists_start.c",
      "east" : DIR + "/rooms/murky_mists/before_dead_end.c",
      "west" : DIR + "/rooms/murky_mists/before_obelisk.c"
   ]));
}
