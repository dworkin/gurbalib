#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A small storage room");
   set_long("you are in a small and dusty storage room.  You can see the " +
      "shop through the opening to the east.");

   add_exit("east", DIR + "/rooms/shop.c");
}
