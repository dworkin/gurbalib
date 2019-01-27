#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("A tunnel in the mountain");
   set_long("You are in a tunnel deep in the mountain. You can see a red glow far away.");

   add_exit("north", FAIRYLAND_ROOMS + "/dragonroom.c");
   add_exit("south", FAIRYLAND_ROOMS + "/mountain.c");

   add_item("glow", "The glow lies to the north, and pulsates rhythmically.");

   set_objects(DIR + "/obj/doors/tunnel.c");
}
