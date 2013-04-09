#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkEast");
   add_area("BorderWalkSouth");
   add_area("GurbaOutdoor");

   set_short("Border Walk - Southeast");
   set_long("You are at the southeast corner of the town of Gurba, " +
      "where the eastern and southern sections of the Border Walk meet. " +
      "At this corner there seems to be an entrance to a small watch tower " +
      "used by the town guards to keep an eye out for undesirables, but " +
      "the entrance is locked. The sounds of the town echo a bit here in " +
      "this semi-enclosed space. Border Walk continues north and west here " +
      "toward other parts of the city.");

   add_item("tower", "The stone tower is built into the wall and is " +
      "accessible via an internal staircase, it seems. Openings at the " +
      "top allow town guards to see any unwanted visitors approaching the " +
      "eastern gate before they arrive.");

   set_exits(([
      "north" : DIR + "/rooms/border_east1",
      "west" : DIR + "/rooms/border_south10",
   ]));
}
