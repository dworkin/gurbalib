#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("A slope in the Den of Chaos in a pocket dimension");
   set_long("You are standing on a slope in the Den of Chaos. " +
      "The slope both inclines and declines to the west from here. " +
      "You cannot say which is actually the case; you are thoroughly " +
      "convinced that it is both at the very same time although that " +
      "seems impossible. Also although you are deep underground the " +
      "wind howls from the south.");

   set_exits(([
      "south": DIR + "/rooms/den_of_chaos/windy.c",
      "west": DIR + "/rooms/den_of_chaos/slope_start.c"
   ]));
}

int do_listen(void) {
   this_player()->write("You listen to the howling chaos winds from " +
      "the south.");
   TELL_ROOM(this_player(), this_player()->query_Name() + " listens to the " +
      "howling chaos winds from the south.");
   return 1;
}

