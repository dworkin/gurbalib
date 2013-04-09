#include "../../domain.h"

inherit "std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Room wiht black walls");
   set_long("A room with black walls.  There is a door to the east, " +
      "and a door to the west.");

   /* Need to do door stuff here XXX */
   add_exit("east", DIR + "/rooms/well.c");
   add_exit("west", DIR + "/rooms/sub/after_trap.c");
}
