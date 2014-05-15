#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("A cave passage in the Noki Cliffs filled with busts");
   set_long("");

   set_exits(([
      "north" : DIR + "/rooms/cliffs/cave/puzzle_chamber.c",
      "south" : DIR + "/rooms/cliffs/cave/cave_start.c"
   ]));
}

