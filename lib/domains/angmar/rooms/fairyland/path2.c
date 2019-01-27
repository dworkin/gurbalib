#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The path to Misty Mountain");
   set_long("You are on the path to Misty Mountain. You can see the might "
            + "of the mountain encompassed in the sheer size of the object. "
            + "It has stood for eons, and few know of the treasures, secrets, "
            + "and pitfalls within.");

   add_exit("north", FAIRYLAND_ROOMS + "/mountain_foot.c");
   add_exit("east", FAIRYLAND_ROOMS + "/path1.c");

   add_item("path", "The path seems to be less worn now, as if few had travelled it.");
   add_item("misty mountain", "The sheer beauty of the spectacle amazes you.");
   add_item("mountain", "The sheer beauty of the spectacle amazes you.");
}
