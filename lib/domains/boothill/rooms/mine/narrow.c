#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Narrow passage");
   set_long("The cave becomes thiner here.  It takes a sharp turn, it " +
      "looks pretty skinny towards the south.  It might be safer to go " +
      "back west.");


   set_exits(([
      "south" : DIR + "/rooms/mine/rough.c",
      "west" : DIR + "/rooms/mine/split.c",
   ]));
}

