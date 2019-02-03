#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("In a pass of the Noki Cliffs");
   set_long("You are in a pass of the Noki Cliffs. " +
      "You can get out of the the pass in one of two " +
      "ways. The first is to go down. The other is to " +
      "head north which takes you out of a pass and into " +
      "valley. In the valley you can see a small village.");

   add_item("valley", "A small village sets in the valley.");
   add_item("village", "The village is small but well kept. " +
      "You could visit it.");

   set_exits(([
      "down" : DIR + "/rooms/cliffs/pass.c",
      "north" : DIR + "/rooms/town/town_start.c"
   ]));
}
