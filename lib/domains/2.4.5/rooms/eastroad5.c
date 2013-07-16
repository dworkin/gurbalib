#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("East road");
   set_long("East road runs south from here.  To the west lies the " +
      "East Road Inn.");

   add_exit("south", DIR + "/rooms/eastroad4.c");
   add_exit("west", DIR + "/rooms/inn.c");
}
