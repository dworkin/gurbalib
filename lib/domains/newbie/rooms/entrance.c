#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("newbie");

   set_short("Inside a tunnel");
   set_long("You are in a small tunnel.  It was a tight squeeze to get in " +
      "here.");

   set_exits(([
      "south" : DIR + "/rooms/equipment",
      "west" : DIR + "/rooms/tree", 
   ]));
}
