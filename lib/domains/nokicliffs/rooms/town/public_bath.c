#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town public bath");
   set_long("You are at Noki Town's public bath. " +
      "Go east to get your stuff and or return to " +
      "to the town square.");
   set_exits(([
      "east" : DIR + "/rooms/town/self_storage.c"
   ]));
}

