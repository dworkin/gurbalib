#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("A Large opening");
   set_long("This is a really big room in the mine.  It looks like they " +
      "must have hit a major vein in this room.  Someone did some major " +
      "excavation.");

   set_exits(([
      "north" : DIR + "/rooms/mine/split.c",
      "east" : DIR + "/rooms/mine/rough.c",
   ]));
}

