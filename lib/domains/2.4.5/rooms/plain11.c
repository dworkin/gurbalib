#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain.  There is a mountain to the north.");

   add_exit("north", DIR + "/rooms/mount_pass.c");
   add_exit("south", DIR + "/rooms/plain6.c");
   add_exit("east", DIR + "/rooms/plain13.c");
   add_exit("west", DIR + "/rooms/plain12.c");
}
