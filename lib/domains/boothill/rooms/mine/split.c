#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Split");
   set_long("The cavern splits into a fork here.  You can go back west or " +
      "continue further into the cave east or south.");

   set_exits(([
      "south" : DIR + "/rooms/mine/large.c",
      "east" : DIR + "/rooms/mine/narrow.c",
      "west" : DIR + "/rooms/mine/mineent.c",
   ]));
}

