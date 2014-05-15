#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Doomspire level one");
   set_long("Here we can return to the base camp by leaving.");

   set_exits(([
      "up" : DIR + "/rooms/doomspire/second_level_start.c",
      "leave" : NOKICLIFFS_BASE_CAMP
   ]));
}
