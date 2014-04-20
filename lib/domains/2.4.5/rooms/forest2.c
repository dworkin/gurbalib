#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("In a forest");
   set_long("You are in a big forest.");

   add_exit("east", DIR + "/rooms/clearing.c");
   add_exit("west", DIR + "/rooms/slope.c");

  set_objects (DIR + "/monsters/troll.c");
}
