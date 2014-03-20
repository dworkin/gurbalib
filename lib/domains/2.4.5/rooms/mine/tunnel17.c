#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("The tunnel into the mines.");

   add_exit("north", DIR + "/rooms/mine/tunnel19.c");
   add_exit("south", DIR + "/rooms/mine/tunnel16.c");
   add_exit("west", DIR + "/rooms/mine/tunnel18.c");
}
