#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Fields");
   set_long("You are in the middle of the fields where the city grows " +
      "all its crops.  A road runs north of here.");

   add_exit("north", DIR + "/rooms/vill_shore.c");
}
