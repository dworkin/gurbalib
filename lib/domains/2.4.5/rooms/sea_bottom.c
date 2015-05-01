#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Sea bottom");
   set_long("You are at the bottom of the sea.");

   add_exit("up", DIR + "/rooms/sea.c");

   set_objects (DIR + "/monsters/octopus.c");
#ifdef USE_NOKICLIFFS
   add_object(NOKICLIFFS_SEASHELL, 1);
#endif
}
