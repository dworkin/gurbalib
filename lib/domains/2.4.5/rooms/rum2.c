#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Room 2");
   set_long("This is room 2.  There is an exit to the west.");

   add_exit("west", DIR + "/rooms/test.c");
}

// XXX Need to get doors working? for the exit west...
