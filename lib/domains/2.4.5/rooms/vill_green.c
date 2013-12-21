#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Village green");
   set_long("You are at an open green place south of the village church.  " +
      "You can see a road further to the east.");

   add_exit("north", DIR + "/rooms/church.c");
   add_exit("east", DIR + "/rooms/vill_track.c");
   add_exit("west", DIR + "/rooms/hump.c");
}
