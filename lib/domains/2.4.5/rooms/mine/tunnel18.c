inherit "/std/room";

#include "../../domain.h"

void setup(void) {
   add_area("2.4.5");

   set_short("Dead end");
   set_long("In the tunnel into the mines.");

   add_exit("east", DIR + "/rooms/mine/tunnel17.c");
}
