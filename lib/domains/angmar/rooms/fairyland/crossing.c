#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("Crossing");
   set_long("The road crossing. An old wooden sign-post points the ways to " +
            "different areas. The road to the north leads to Misty Mountain. " +
            "The village is to the south.");

   add_exit("north", FAIRYLAND_ROOMS + "/path1.c");
   add_exit("south", FAIRYLAND_ROOMS + "/road3.c");
   add_exit("east", FAIRYLAND_ROOMS + "/lake_road.c");

   add_item("road", "The road seems worn, as if many adventurers have travelled upon it.");
   add_item("sign-post", "The sign points east to Great Lake.");
   add_item("sign post", "The sign points east to Great Lake.");
   add_item("sign", "The sign points east to Great Lake.");
   add_item("post", "It's old and weather-beaten. It looks like it will fall apart.");
   add_item("lake", "Great Lake, off to the east. You need to go closer to see it.");
   add_item("village", "The village lies off to the south.");
}
