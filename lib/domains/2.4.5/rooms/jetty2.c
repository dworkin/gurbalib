#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Jetty");
   set_long("You are at a jetty.  The waves roll in from the east.  " +
      "A small path leads back to the west.");

   add_exit("east", DIR + "/rooms/sea.c");
   add_exit("west", DIR + "/rooms/vill_shore2.c");

  set_objects (DIR + "/obj/bag.c");
}
