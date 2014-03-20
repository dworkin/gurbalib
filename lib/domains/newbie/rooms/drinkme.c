#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("newbie");

   set_short("Waiting area");
   set_long("You are in a small tunnel.  This room looks like a small " +
      "waiting area.  You hear loud noises to the north.");

   set_exits(([
      "north" : DIR + "/rooms/fighting", 
      "south" : DIR + "/rooms/quest",
   ]));

   set_objects(DIR + "/obj/table");
}
