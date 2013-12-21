#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkSouth");
   add_area("GurbaOutdoor");

   set_short("Border Walk - South");
   set_long("You are on the Border Walk, the long and narrow street " +
      "which surrounds the town of Gurba in a large rectangle. It runs " +
      "along the inside edge of the stone town wall, which at the moment " +
      "lies to your south. The walk continues from here to the east and " +
      "west. On the north side of the road seems to be a small restaurant " +
      "of some kind, with the occasional group of people coming or going.");

   set_exits(([
      "west" : DIR + "/rooms/border_south2",
      "east" : DIR + "/rooms/border_south4",
      "north" : DIR + "/rooms/restaurant",
   ]));
}
