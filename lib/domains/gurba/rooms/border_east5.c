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
      "lies to your east. The walk runs to the north from here. " +
      "Immediately to the south you can see the impressive stone archway " +
      "of the eastern city gate.");

   set_exits(([
      "south" : DIR + "/rooms/gate_east",
      "north" : DIR + "/rooms/border_east6",
   ]));
}
