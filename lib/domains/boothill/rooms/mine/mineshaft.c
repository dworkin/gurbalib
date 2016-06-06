#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Mine shaft");
   set_long("You are in the bowels of the mountain now.  There is a large " +
      "rusty Iron door here to the west.");

   set_exits(([
      "west" : DIR + "/rooms/mine/bigrock.c",
      "east" : DIR + "/rooms/mine/escape.c",
   ]));

   set_objects(DIR + "/obj/irondoor.c");
}

