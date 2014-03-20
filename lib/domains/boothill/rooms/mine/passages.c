#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Passages");
   set_long("There are multiple passages here, your not sure which way " +
      "to go.");

   set_exits(([
      "north" : DIR + "/rooms/mine/bigrock.c",
      "east" : DIR + "/rooms/mine/deadend.c",
      "west" : DIR + "/rooms/mine/station.c",
   ]));
}

