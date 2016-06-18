#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Candyland village in a pocket dimension");
   set_long("The long description and some exits and stuff.");

   set_exits(([
      "south" : DIR + "/rooms/candyland/candyland_start.c"
   ]));
}

