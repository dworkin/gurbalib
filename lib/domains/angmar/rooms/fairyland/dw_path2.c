#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_light(0);
   set_short("On a path in Darkwood");
   set_long("You are on a twisty path in the legendary Darkwood. " +
      "You feel very uncomfortable.");

   add_exit("north", FAIRYLAND_ROOMS + "/dw_path3.c");
   add_exit("south", FAIRYLAND_ROOMS + "/dw_path1.c");
   add_exit("east", FAIRYLAND_ROOMS + "/darkwood1.c");

   add_item("path", "The path twists and turns as it weaves its way into Darkwood.");
   add_item("darkwood", "The forest gets more evil now, and light is frequently blocked by the trees.");

   set_objects(DIR + "/monsters/big_oak.c");
}
