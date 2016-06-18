#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("The Abbey of Law's lobby");
   set_long("You are in the lobby of the Abbey of Law.");

   set_exits(([
      "east" : DIR + "/rooms/abbey_of_law/hallway.c",
      "west" : DIR + "/rooms/abbey_of_law/abbey_of_law_start.c"
   ]));
}
