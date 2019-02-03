#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("Misty Mountain");
   set_long("You are climbing Misty Mountain. There is a door set into the rock before you to the north.");

   add_exit("up", FAIRYLAND_ROOMS + "/mountain_top.c");
   add_exit("down", FAIRYLAND_ROOMS + "/mountain_foot.c");
   add_exit("north", FAIRYLAND_ROOMS + "/tunnel.c");
   add_exit("east", FAIRYLAND_ROOMS + "/rock_ledge.c");

   set_objects(DIR + "/obj/doors/mountain.c");
}
