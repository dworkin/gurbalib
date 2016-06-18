#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A cave entrance in the Noki Cliffs");
   set_long("You are standing at the entrance of a cave in the Noki Cliffs. " +
      "It is not clear how large the cave is from here as it turns into " +
      "complete darkness not very deep into it. The cave does strike you " +
      "dangerous and uninviting. The ledge goes to the east from here " +
      "while walking north takes you into the cave itself. If you are " +
      "careful you can climb up here without any climbing gear.");

   set_exits(([
      "up" : DIR + "/rooms/cliffs/base_camp.c",
      "north" : DIR + "/rooms/cliffs/cave/bust_chamber.c",
      "east" : DIR + "/rooms/cliffs/ledge.c"
   ]));
}
