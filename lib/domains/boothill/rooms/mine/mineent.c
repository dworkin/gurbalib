#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Entrance to the mine");
   set_long("You came into the mine and the exit collapsed behind you.  It " +
      "doesn't look like you'll be getting out of the mine here.  The " +
      "mine continues deeper into the cave to the east.");

   set_exits(([
      "east" : DIR + "/rooms/mine/split.c",
   ]));
}
