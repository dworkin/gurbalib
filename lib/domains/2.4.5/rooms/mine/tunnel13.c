#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("End of the tunnel.");

   add_exit("south", DIR + "/rooms/mine/tunnel12.c");
}
