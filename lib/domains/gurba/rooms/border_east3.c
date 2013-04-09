#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkEast");
   add_area("GurbaOutdoor");

   set_short("Border Walk - East");
   set_long("You are on the Border Walk, the long and narrow street " +
      "which surrounds the town of Gurba in a large rectangle. It runs " +
      "along the inside edge of the stone town wall, which at the moment " +
      "lies to your east. The walk runs to the north and south from here. " +
      "To the north lies the eastern town gate.");

   set_exits(([
      "south" : DIR + "/rooms/border_east2",
      "north" : DIR + "/rooms/border_east4",
   ]));
}
