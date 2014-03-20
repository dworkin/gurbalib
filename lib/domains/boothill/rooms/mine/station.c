#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("The Station");
   set_long("This use to be the supply station for the mine.  There are a " +
      "number of shelves and abandoned mine carts here.  Back in the " +
      "day you could have stocked up big time.");

   set_exits(([
      "north" : DIR + "/rooms/mine/cavein.c",
      "east" : DIR + "/rooms/mine/passages.c",
      "west" : DIR + "/rooms/mine/squeeze.c",
   ]));

   set_objects(DIR + "/obj/pickaxe.c");
}
