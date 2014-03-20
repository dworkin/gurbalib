#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("The tunnel slopes steeply up here.");

   add_exit("north", DIR + "/rooms/mine/tunnel26.c");
   add_exit("up", DIR + "/rooms/mine/tunnel24.c");
}
