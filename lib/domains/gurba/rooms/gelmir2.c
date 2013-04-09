#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GelmirRoad");
   add_area("GurbaOutdoor");

   set_short("Gelmir Road");
   set_long("Gelmir Road is one of the busier streets in the city of " +
      "Gurba.  Inhabitants of the town and visitors from abroad pass " +
      "by in both directions, attending to their various errands and " +
      "business.  To the east lies the entrance to the Fighter's Guild.  " +
      "Further to the west you can see the town square.");

   set_exits(([
      "east" : DIR + "/rooms/gelmir3",
      "west" : DIR + "/rooms/gelmir1",
   ]));
}
