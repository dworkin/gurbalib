#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("In the dragon's cave");
   set_long("This is where the great dragon lives and hoards treasures.");

   add_exit("south", FAIRYLAND_ROOMS + "/tunnel.c");

   add_item("treasures", "The usual things a dragon collects over a lifetime.");

   set_objects(DIR + "/monsters/smaug.c");
}
