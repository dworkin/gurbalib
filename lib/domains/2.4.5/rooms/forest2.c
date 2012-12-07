#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("In a forest");
   set_long("You are in a big forest.");

   add_exit("east", DIR + "/rooms/clearing.c");
   add_exit("west", DIR + "/rooms/slope.c");

  set_objects (([
   DIR + "/monsters/troll.c": 1,
  ]));
}
