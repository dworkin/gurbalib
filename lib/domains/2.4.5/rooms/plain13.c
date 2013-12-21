#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain.  There is a mountain to the north, " +
      "but it is too steep to climb.");

   add_exit("south", DIR + "/rooms/plain8.c");
   add_exit("west", DIR + "/rooms/plain11.c");
}
