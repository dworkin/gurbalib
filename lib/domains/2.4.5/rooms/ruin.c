#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Ruin");
   set_long("A very old looking ruin.  There is no roof, and no door.");

   add_exit("north", DIR + "/rooms/plain4.c");
   add_exit("south", DIR + "/rooms/plain8.c");
   add_exit("east", DIR + "/rooms/plain9.c");
   add_exit("west", DIR + "/rooms/plain3.c");
}
