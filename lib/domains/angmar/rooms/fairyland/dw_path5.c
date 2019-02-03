#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("On a path in Darkwood");
   set_long("The forest ends to the west.");

   add_exit("north", FAIRYLAND_ROOMS + "/darkwood5.c");
   add_exit("east", FAIRYLAND_ROOMS + "/dw_path4.c");
   add_exit("west", FAIRYLAND_ROOMS + "/behind_mountain.c");

   add_item("west", "The forest ends, finally.");
   add_item("forest", "The forest has thinned out slightly. Could you be out of it? Perhaps...");
}
