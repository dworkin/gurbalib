#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A puzzling cave chamber in the Noki Cliffs");
   set_long("You are in a small chamber within the Noki Cliffs cave. " +
      "You can only go north or south from here, but the way north " +
      "requires you to solve a puzzle first. On the wall next to the " +
      "way north is the puzzle. It's been smashed to bits. That's not " +
      "always the best way to solve puzzles, but it seems to have " +
      "worked this time.");
   set_exits(([
      "north" : DIR + "/rooms/cliffs/cave/brain_room.c",
      "south" : DIR + "/rooms/cliffs/cave/bust_chamber.c"
   ]));
}

