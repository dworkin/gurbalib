#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_light(1);
   set_short("On a path in Darkwood");
   set_long("You are on a twisty path in the legendary Darkwood. " +
            "You feel lucky to still be alive.");

   add_exit("north", FAIRYLAND_ROOMS + "/darkwood3.c");
   add_exit("south", FAIRYLAND_ROOMS + "/darkwood4.c");
   add_exit("east", FAIRYLAND_ROOMS + "/dw_path3.c");
   add_exit("west", FAIRYLAND_ROOMS + "/dw_path5.c");

   add_item("path", "The path is becoming more and more faint. Best hope you do not lose it.");
   add_item("darkwood", "The forest gets more evil now, and light is frequently blocked by the trees.");
}
