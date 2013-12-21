#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("The tunnel slopes steeply down a hole here.");

   add_exit("west", DIR + "/rooms/mine/tunnel23.c");
   add_exit("down", DIR + "/rooms/mine/tunnel25.c");
}
