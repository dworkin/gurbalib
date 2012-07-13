#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("Main street");
   set_long("You are on main street, infront of a large saloon, to your " +
      "east.");

   set_exits(([
      "north" : DIR + "/rooms/infront_store.c", 
      "south" : DIR + "/rooms/entrance.c", 
      "east" : DIR + "/rooms/saloon.c", 
   ]));
}
