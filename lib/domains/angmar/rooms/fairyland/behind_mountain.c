#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Behind the Misty Mountain");
   set_long("The path ends here behind Misty Mountain. There seems to be no way around it.");

   add_exit("east", FAIRYLAND_ROOMS + "/dw_path5.c");

   add_item("path", "It stops all of a sudden. You cannot follow it anymore.");
   add_item("mountain", "It dwarfs you, looming in the sky.");
   add_item("misty mountain", "It dwarfs you, looming in the sky.");

   set_objects(DIR + "/monsters/troll_king.c");
}
