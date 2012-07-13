#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The shop");
   set_long("You are in a shop.  You can buy or sell things here.  " +
      "There is an opening to the north, and some shimmering blue light " +
      "in the doorway.  To the west you can see a small room.");

   add_exit("south", DIR + "/rooms/vill_road2.c");
   add_exit("west", DIR + "/rooms/storage.c");
}

// XXX Need to do store stuff here...
