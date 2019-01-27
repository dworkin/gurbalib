#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The foot of Misty Mountain");
   set_long("Misty Mountain towers high before you. You feel very small.");

   add_exit("up", FAIRYLAND_ROOMS + "/mountain.c");
   add_exit("south", FAIRYLAND_ROOMS + "/path2.c");

   add_item("misty mountain", "The mountain is huge, but you think you can climb up.");
   add_item("mountain", "The mountain is huge, but you think you can climb up.");
}
