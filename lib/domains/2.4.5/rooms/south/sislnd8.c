#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of the Isle of the Magi");
   set_long("You are standing on the shore of the isle of the Magi.  " +
      "A path leads up the hill to the east.  " +
      "The shore of the island continues southeast and northwest into a " +
      "small grove from here.  To the north, you can see an old disused well.");

   add_exit("north", DIR + "/rooms/south/sislnd17.c");
   add_exit("east", DIR + "/rooms/south/sislnd16.c");
   add_exit("southeast", DIR + "/rooms/south/sislnd7.c");
   add_exit("northwest", DIR + "/rooms/south/sislnd9.c");
}
