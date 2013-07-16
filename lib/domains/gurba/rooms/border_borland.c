#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkNorth");
   add_area("GurbaOutdoor");

   set_short("Intersection of Border Walk/Borland Avenue");
   set_long("Here, the long rectangular Border Walk crosses the end of " +
      "Borland Avenue, a small but well-maintained residential district " +
      "of the town, which leads to the south from here. The sounds of " +
      "children playing can be heard. The Border Walk continues to the " +
      "east and west.");

   set_exits(([
      "east" : DIR + "/rooms/border_north6",
      "west" : DIR + "/rooms/border_north5",
      "south" : DIR + "/rooms/borland3",
   ]));
}
