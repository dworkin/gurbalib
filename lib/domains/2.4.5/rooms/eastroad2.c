#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("East road");
   set_long("East road runs north-south.");

   add_exit("north", DIR + "/rooms/eastroad3.c");
   add_exit("south", DIR + "/rooms/eastroad1.c");
}
