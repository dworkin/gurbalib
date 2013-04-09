#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkWest");
   add_area("GurbaOutdoor");

   set_short("Border Walk - West");
   set_long("You are on the Border Walk, the long and narrow street " +
      "which surrounds the town of Gurba in a large rectangle. It runs " +
      "along the inside edge of the stone town wall, which at the moment " +
      "lies to your west. The walk runs to the north and south from here. " +
      "To the south lies the western town gate. To the north you can see " +
      "the towers of the sprawling Gurba University.");

   set_exits(([
      "south" : DIR + "/rooms/border_west5",
      "north" : DIR + "/rooms/border_west7",
   ]));
}
