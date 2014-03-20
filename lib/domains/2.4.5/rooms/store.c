#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Store room for the shop");
   set_long("All things from the shop are stored here. Or they use to " +
      "be at any rate.  It looks like this room hasn't been touched in ages.");
   add_exit("south", DIR + "/rooms/shop.c");
}
