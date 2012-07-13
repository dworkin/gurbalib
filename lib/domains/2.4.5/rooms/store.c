#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Store room for the shop");
   set_long("All things from the shop are stored here.");
   add_exit("south", DIR + "/rooms/shop.c");
}

// XXX Need to do store stuff here...
