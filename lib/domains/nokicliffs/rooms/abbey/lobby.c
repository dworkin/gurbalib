#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("The Abbey's lobby");
   set_long("You are in the lobby of the Abbey.");

   set_exits(([
      "east" : DIR + "/rooms/abbey/hallway.c",
      "west" : DIR + "/rooms/abbey/abbey_start.c"
   ]));
}
