#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - Northwest");
   set_long("The northwestern corner of the town square is a busy " +
      "place, though not quite as busy as the surrounding areas.  You " +
      "can hear quite a commotion to the east, and the enthusiastic " +
      "cries of produce salesmen to the south.  There seems to be a " +
      "steady stream of people coming in and out of the pub to the north.");

   set_exits(([
      "east" : DIR + "/rooms/square_north",
      "south" : DIR + "/rooms/square_west",
      "southeast" : DIR + "/rooms/square_center",
   ]));
}
