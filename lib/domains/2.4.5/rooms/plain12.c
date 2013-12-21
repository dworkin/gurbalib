#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain.  There is a forest to the west.");

   add_exit("south", DIR + "/rooms/plain10.c");
   add_exit("east", DIR + "/rooms/plain11.c");
   add_exit("west", DIR + "/rooms/deep_forest1.c");
}
