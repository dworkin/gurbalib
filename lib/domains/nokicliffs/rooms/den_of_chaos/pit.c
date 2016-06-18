#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A pit in the Den of Chaos in a pocket dimension");
   set_long("You are in a pit. Winds whip around in utter chaos. It is " +
      "difficult but still possible to hear.");

   set_exits(([
      "west": DIR + "/rooms/den_of_chaos/windy.c"
   ]));

   set_objects(NOKICLIFFS_MONSTERS_DIR + "/apep");
}

int do_listen(void) {
   this_player()->write("You listen to the howling chaos winds.");
   TELL_ROOM(this_player(), this_player()->query_Name() + " listens to the " +
      "howling chaos winds.");
   return 1;
}

