#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain, extending to the north and south.");

   add_exit("north", DIR + "/rooms/plain3.c");
   add_exit("south", DIR + "/rooms/plain1.c");
   add_exit("east", DIR + "/rooms/plain4.c");
   add_exit("west", DIR + "/rooms/plain5.c");
}
