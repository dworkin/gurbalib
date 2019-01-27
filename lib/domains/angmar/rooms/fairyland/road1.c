#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("On a road in Fairyland");
   set_long("You are standing on a road in Fairyland. The road " +
      "continues to the north.");

   add_exit("north", FAIRYLAND_ROOMS + "/road2.c");
   add_exit("south", FAIRYLAND_ROOMS + "/edge1.c");

   add_item("road", "The road has a magical quality to it. This realm is different, somehow.");
   add_item("fairyland", "You can't possibly see all of it from here.");
}
