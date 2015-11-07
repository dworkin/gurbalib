#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Mine entrance");
   set_long("This is the entrance to the mines.  There is a sign on a pole.");

   add_exit("north", DIR + "/rooms/mine/tunnel2.c");
   add_exit("south", DIR + "/rooms/mount_pass.c");

   add_item("sign", "WARNING!!\n\nThe mines are closed due to risk of " +
      "falling rock.");
}
