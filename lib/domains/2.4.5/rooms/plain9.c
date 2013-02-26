#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_short("A large open plain");
   set_long("A large open plain.  There is a river to the east and " +
      "some kind of building to the west.");

   add_exit("north", DIR + "/rooms/plain13.c");
   add_exit("south", DIR + "/rooms/ruin.c");
   add_exit("west", DIR + "/rooms/plain6.c");

   set_objects (([
      DIR + "/monsters/frog.c": 1,
      DIR + "/obj/stethoscope.c": 1,
   ]));
}
