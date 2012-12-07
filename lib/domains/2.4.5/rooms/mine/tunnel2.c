#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("In the tunnel into the mines.");

   add_exit("north", DIR + "/rooms/mine/tunnel3.c");
   add_exit("south", DIR + "/rooms/mine/tunnel.c");
}
