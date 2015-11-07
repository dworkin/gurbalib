#include "../../domain.h"
inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A dimly lit forest");
   set_long("You are in part of a dimly lit forest.  " +
      "Trails lead north, south and west.");

   add_exit("north", DIR + "/rooms/forest12.c");
   add_exit("south", DIR + "/rooms/south/sforst2.c");
   add_exit("west", DIR + "/rooms/south/sforst5.c");
}
