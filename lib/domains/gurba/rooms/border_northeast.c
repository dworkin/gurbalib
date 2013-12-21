#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkEast");
   add_area("BorderWalkNorth");
   add_area("GurbaOutdoor");

   set_short("Border Walk - Northeast");
   set_long("You are at the northeast corner of the town of Gurba, " +
      "where the eastern and southern sections of the Border Walk meet. " +
      "It is really quiet and peaceful here. A few benches have been " +
      "scattered around a large, old-looking tree that is planted at the " +
      "very corner of the wall. Border Walk continues south and west here " +
      "toward other parts of the town.");

   add_item("tree", "This ancient oak tree is far taller than the wall.  " +
      "Its gnarled branches offer a shady place to relax.");

   set_exits(([
      "south" : DIR + "/rooms/border_east8",
      "west" : DIR + "/rooms/border_north10",
   ]));
}
