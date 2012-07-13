#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Sea bottom");
   set_long("You are at the bottom of the sea.");

   add_exit("up", DIR + "/rooms/sea.c");

   set_objects (([
      DIR + "/monsters/octopus.c": 1,
   ]));
}
