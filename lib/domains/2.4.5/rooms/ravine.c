#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Ravine");
   set_long("You are in a ravine between mountains.  It seems to be " +
      "possible to go up from here.");

   add_exit("up", DIR + "/rooms/mount_top.c");
   add_exit("down", DIR + "/rooms/mount_pass.c");
}
