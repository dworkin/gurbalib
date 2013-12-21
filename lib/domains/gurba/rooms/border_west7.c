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
      "lies to your west. This particular section of the road is " +
      "particularly busy; to the east there is a large iron gate which " +
      "marks the entrance to Gurba University. Students come and go in " +
      "various states of preoccupation. To the south lies the western " +
      "city gate.");

   set_exits(([
      "south" : DIR + "/rooms/border_west6",
      "north" : DIR + "/rooms/border_west8",
   ]));
}
