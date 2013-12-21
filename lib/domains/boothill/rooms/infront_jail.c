#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Outside the jail");
   set_long("You are on main street, in front of the town jail.  Main " +
      "runs north and south while the jail is to your east.");

   set_exits(([
      "north" : DIR + "/rooms/boothill.c", 
      "south" : DIR + "/rooms/infront_store.c", 
      "east" : DIR + "/rooms/jail.c", 
   ]));
}
