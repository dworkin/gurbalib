#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain, extending to the north and south.");

   add_exit("north", DIR + "/rooms/plain2.c");
   add_exit("south", DIR + "/rooms/clearing.c");

   set_objects (DIR + "/monsters/wolf.c");
}
