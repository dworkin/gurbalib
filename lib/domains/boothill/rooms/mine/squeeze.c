#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Tight squeeze");
   set_long("The mine is really narrow here.  You wonder why they skimped " +
      "on this section.  The timer supports are only half the width of " +
      "the rest of the mine.");

   set_exits(([
      "east" : DIR + "/rooms/mine/station.c",
      "west" : DIR + "/rooms/mine/rough.c",
   ]));

   set_objects(DIR + "/monsters/kobold.c");
}

