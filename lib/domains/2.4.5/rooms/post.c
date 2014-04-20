#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The post office");
   set_long("An abandoned post office.\n");

   add_exit("north", DIR + "/rooms/narr_alley.c");
}
