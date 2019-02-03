#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A windy tunnel in the Den of Chaos in a pocket dimension");
   set_long("You are in a windy tunnel of the Den of Chaos. The chaos " +
      "winds are strong here. A closer looks reveals the source of the " +
      "winds is a pit to the east.");

   set_exits(([
      "east": DIR + "/rooms/den_of_chaos/pit.c",
      "north": DIR + "/rooms/den_of_chaos/slope_end.c"
   ]));
}

int do_listen(void) {
   this_player()->write("You listen to the howling chaos winds sourced " +
      "from a pit to the east.");
   TELL_ROOM(this_player(), this_player()->query_Name() + " listens to the " +
      "howling chaos winds sourced from a pit to the east.");
   return 1;
}
