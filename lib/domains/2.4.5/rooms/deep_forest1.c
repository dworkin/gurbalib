#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Deep forest");
   set_long("In the deep forest.  The wood lights up to the east.");

   add_exit("east", DIR + "/rooms/plain12.c");
}
