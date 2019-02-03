#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_light(0);

   set_short("Deep inside Darkwood");
   set_long("You are deep inside Darkwood. You wish you had never come here.");

   add_exit("south", FAIRYLAND_ROOMS + "/dw_path5.c");
   add_exit("east", FAIRYLAND_ROOMS + "/darkwood3.c");

   set_objects(DIR + "/monsters/giant_oak.c");
}
