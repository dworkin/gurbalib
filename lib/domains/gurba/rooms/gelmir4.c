#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaOutdoor");
   add_area("GelmirRoad");

   set_short("Gelmir Road");
   set_long("This is one of the busier parts of one of the town's " +
      "busiest streets. To the east lies the eastern gate of the town, " +
      "while to the west sits the intimidatingly large dome of the " +
      "Fighter's Guild. Large crowds of people wander past, some " +
      "headed toward the town square in the distance to the west.");

   set_exits(([
      "east" : DIR + "/rooms/gate_east",
      "west" : DIR + "/rooms/gelmir3",
   ]));
}
