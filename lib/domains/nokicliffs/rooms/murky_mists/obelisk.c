#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Murky mists hammock");
   set_long("You are on a hammock within the murky mists. " +
      "It inclines somewhat to the north, representing the " +
      "largest elevation found in the area; standing upon " +
      "the mound of earth is a tall obelisk and its top " +
      "disappears in the mist.");

   set_exits(([
      "south" : DIR + "/rooms/murky_mists/before_obelisk.c"
   ]));

   add_item("obelisk", "The top of the obelisk disappears " +
      "into the mysterious myst, but what you can make " +
      "out from the markings on the obelisk is that it " +
      "tells a story about two women on a dragon hunt on " +
      "one of the outer planes.");

   set_objects(DIR + "/monsters/swamp_beast.c");
}
