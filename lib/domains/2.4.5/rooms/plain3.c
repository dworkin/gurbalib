#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain, There is some kind of building to the east.");

   add_exit("north", DIR + "/rooms/plain6.c");
   add_exit("south", DIR + "/rooms/plain2.c");
   add_exit("east", DIR + "/rooms/ruin.c");
   add_exit("west", DIR + "/rooms/plain7.c");
}
