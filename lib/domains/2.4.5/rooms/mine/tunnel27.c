#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Dead end");
   set_long("End of tunnel!");

   add_exit("south", DIR + "/rooms/mine/tunnel26.c");
}
