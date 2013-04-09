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
      "lies to your south. Immediately to the west the road reaches a " +
      "corner, and it continues to the east towards other parts of the town.");

   set_exits(([
      "west" : DIR + "/rooms/border_southwest",
      "east" : DIR + "/rooms/border_south2",
   ]));
}
