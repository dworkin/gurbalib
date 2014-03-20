#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A dimly lit forest");
   set_long("You are in part of a dimly lit forest.  " +
      "Trails lead south and east.");

   add_exit("south", DIR + "/rooms/south/sforst6.c");
   add_exit("east", DIR + "/rooms/south/sforst1.c");
}
