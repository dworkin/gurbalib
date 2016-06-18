#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town edge of civilisation");
   set_long("You are at the edge of Noki Town. " +
      "If you continue east you will enter the " +
      "wilderness. The town square is to the west.");
   set_exits(([
      "east" : DIR + "/rooms/town/wilderness.c",
      "west" : DIR + "/rooms/town/square_north.c"
   ]));
   set_objects(NOKICLIFFS_TOWN_SO_LONG_SIGN);
}

