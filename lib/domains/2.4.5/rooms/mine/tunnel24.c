#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("The tunnel slopes steeply down a hole here.");

   add_exit("west", DIR + "/rooms/mine/tunnel23.c");
   add_exit("down", DIR + "/rooms/mine/tunnel25.c");
}
