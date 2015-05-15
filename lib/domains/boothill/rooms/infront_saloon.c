#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Main street");
   set_long("You are on main street, in front of a large saloon, to your " +
      "east.");

   set_exits(([
      "north" : DIR + "/rooms/infront_store.c", 
      "south" : DIR + "/rooms/welcome.c", 
      "east" : DIR + "/rooms/saloon.c", 
   ]));

   set_objects(
      DIR + "/monsters/slims"
   );
}
