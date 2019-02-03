#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Doomspire level three");
   set_long("You are in the third level of the Doomspire. " +
      "You sense your impending doom. A staircase spirals " +
      "up from here.");

   set_exits(([
      "up" : DIR + "/rooms/doomspire/fourth_level_start.c",
      "north" : DIR + "/rooms/doomspire/third_level_start.c"
   ]));

   set_objects(
      DIR + "/monsters/angmar_wannabe.c",
      DIR + "/obj/inert_automaton.c"
   );
}
