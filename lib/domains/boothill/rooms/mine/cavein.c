#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Cave in");
   set_long("The supports here have collapsed.  There use to be a " +
      "crawlspace to the west, however it doesn't look like your getting " +
      "through that way anymore.");

   set_exits(([
      "south" : DIR + "/rooms/mine/station.c",
      "east" : DIR + "/rooms/mine/bigrock.c",
   ]));

   set_objects(DIR + "/obj/rubble.c");
}

