#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("Outside the general store");
   set_long("You are on main street, infront of the general store.  Main " +
      "runs north and south while the general store is to your west.  " +
      "The road, if you can call it that, seems paticularily muddy here.");

   set_exits(([
      "north" : DIR + "/rooms/infront_jail.c", 
      "south" : DIR + "/rooms/infront_saloon.c", 
      "west" : DIR + "/rooms/general_store.c", 
   ]));
}
