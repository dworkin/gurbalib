#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village church");
   set_long("You are in the local village church.  There is a huge " +
      "pit in the center, and a adoor in the west wall.  " +
      "There is a button beside the door.  This church has the service " +
      "of reviving ghosts.  Dead people come to the church and pray.  " +
      "there is a clock on the wall.  There is an exit to the south.");

   add_exit("north", DIR + "/rooms/vill_shore.c");
}

// XXX Lots of work needed...
