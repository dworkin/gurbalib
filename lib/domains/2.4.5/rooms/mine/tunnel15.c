#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("In the tunnel into the mines.");

   add_exit("east", DIR + "/rooms/mine/tunnel16.c");
   add_exit("west", DIR + "/rooms/mine/tunnel14.c");
}
