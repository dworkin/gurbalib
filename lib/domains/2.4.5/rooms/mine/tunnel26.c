#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("In the tunnel.");

   add_exit("north", DIR + "/rooms/mine/tunnel27.c");
   add_exit("south", DIR + "/rooms/mine/tunnel25.c");
   add_exit("east", DIR + "/rooms/mine/tunnel28.c");
}
