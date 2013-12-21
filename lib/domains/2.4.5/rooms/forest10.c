#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Deep forest");
   set_long("You are in the deep forest.");

   add_exit("east", DIR + "/rooms/forest7.c");
   add_exit("west", DIR + "/rooms/forest9.c");
}
