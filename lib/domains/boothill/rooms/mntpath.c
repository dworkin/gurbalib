#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Along a mountain path");
   set_long("This narrow path winds it's way through the woods, leading " +
      "east and west.");

   set_exits(([
      "east" : DIR + "/rooms/mountain.c",
      "west" : DIR + "/rooms/boothill.c",
   ]));
}
