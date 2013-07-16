#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Top of mountain");
   set_long("You are on top of a mountain.  There is a small plateau to the " +
      "east.");

   add_exit("east", DIR + "/rooms/mount_top2.c");
   add_exit("down", DIR + "/rooms/ravine.c");
}
