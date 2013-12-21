#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Clearing");
   set_long("A small clearing.  There are trees all around you.  However, " +
      "the trees are sparse to the north.");

   add_exit("north", DIR + "/rooms/plain1.c");
   add_exit("east", DIR + "/rooms/forest1.c");
   add_exit("west", DIR + "/rooms/forest2.c");
}
