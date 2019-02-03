#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town entrance");
   set_long("You are in a valley and are standing " +
      "at the entrance to Noki Town. " +
      "It's more of a village than a town and you can tell "+
      "that the people " +
      "are friendly. Being a long way from home you will " +
      "find some very welcomed creature comforts in town. " +
      "Head north from here to enter the town square. " +
      "Going south from here takes up up into a pass through " +
      "Noki Cliffs.");
   set_exits(([
      "north" : DIR + "/rooms/town/square_south.c",
      "south" : DIR + "/rooms/cliffs/pass_top.c"
   ]));
   set_objects(NOKICLIFFS_TOWN_WELCOME_SIGN);
}

