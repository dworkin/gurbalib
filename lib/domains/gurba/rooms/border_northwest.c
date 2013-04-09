#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkWest");
   add_area("BorderWalkNorth");
   add_area("GurbaOutdoor");

   set_short("Border Walk - Northwest");
   set_long("You are at the northwest corner of the town of Gurba, " +
      "where the western and southern sections of the Border Walk meet. " +
      "It is really quiet and peaceful here. A few benches have been " +
      "scattered around a large, old-looking tree that is planted at the " +
      "very corner of the wall. Border Walk continues south and east here " +
      "toward other parts of the town.");

   add_item("tree", "This ancient oak tree is far taller than the wall.  " +
      "Its gnarled branches offer a shady place to relax.");

   set_exits(([
      "south" : DIR + "/rooms/border_west8",
      "east" : DIR + "/rooms/border_north1",
   ]));
}
