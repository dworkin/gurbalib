#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Village shore");
   set_long("The village shore.  A jetty leads out to the east.  To the " +
      "north some stairs lead down to the north beach.  " +
      "A road starts to the west");

   add_exit("east", DIR + "/rooms/jetty2.c");
   add_exit("west", DIR + "/rooms/jetty.c");
}
