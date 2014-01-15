#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Rough spot");
   set_long("The walls here are not as clean cut as the rest of the mine." +
      "  It looks like they must have struck it rich some where else and " +
      "decided there were better places to dig.");

   set_exits(([
      "north" : DIR + "/rooms/mine/narrow.c",
      "east" : DIR + "/rooms/mine/squeeze.c",
      "west" : DIR + "/rooms/mine/large.c",
   ]));
}

