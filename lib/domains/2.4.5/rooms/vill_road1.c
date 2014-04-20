#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Village road");
   set_long("A long road going east through the village.  The road narrows " +
      "to a track to the west.  There is an alley to the north and the south");

   add_exit("north", DIR + "/rooms/yard.c");
   add_exit("south", DIR + "/rooms/narr_alley.c");
   add_exit("east", DIR + "/rooms/vill_road2.c");
   add_exit("west", DIR + "/rooms/vill_track.c");
}
