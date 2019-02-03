#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_light(0);
   set_short("On a path in Darkwood");
   set_long("You are on a twisty path in the legendary Darkwood. " +
            "You can see gleaming eyes stare at you from the shadows.");

   add_exit("north", FAIRYLAND_ROOMS + "/darkwood2.c");
   add_exit("south", FAIRYLAND_ROOMS + "/dw_path2.c");
   add_exit("west", FAIRYLAND_ROOMS + "/dw_path4.c");

   add_item("path", "The path twists and turns as it weaves its way into Darkwood.");
   add_item("darkwood", "The forest gets more evil now, and light is frequently blocked by the trees.");
   add_item("eyes", "They appear red, but then disappear. They reappear momentarily.");
}
