#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("In the tunnel into the mines.");

   add_exit("north", DIR + "/rooms/mine/tunnel17.c");
   add_exit("west", DIR + "/rooms/mine/tunnel15.c");

   set_objects (DIR + "/monsters/dwarf.c");
}
