#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Road");
   set_long("You are on a road going out of the village.  To the east " +
      "the road widens out as it leads down to the shore.  " +
      "To the west lies the city.");

   add_exit("east", DIR + "/rooms/vill_shore2.c");
   add_exit("west", DIR + "/rooms/vill_shore.c");
}
