#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain.");

   add_exit("north", DIR + "/rooms/plain13.c");
   add_exit("south", DIR + "/rooms/ruin.c");
   add_exit("west", DIR + "/rooms/plain6.c");
}
