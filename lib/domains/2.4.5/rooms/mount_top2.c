#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Plateau");
   set_long("You are on a large, open plateau on top of the mountain.  " +
      "The view is fantastic in all directions and the clouds that " +
      "rush past above, feel so close you could almost touch them.  " +
      "The air here is fresh and clean. To the east the legendary " +
		"Noki Cliffs loom large.");

	add_exit("east", "/domains/nokicliffs/rooms/start.c");
   add_exit("west", DIR + "/rooms/mount_top.c");
}
