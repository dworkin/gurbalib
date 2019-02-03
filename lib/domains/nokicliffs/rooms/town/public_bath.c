#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town public bath");
   set_long("You are at Noki Town's public bath. " +
      "Sounds of a casino are heard to the south, " +
      "which is the bottom floor of the only inn " +
      "in Noki Town. The hotel is very popular " +
      "and rarely has vacancy. " +
      "Go east to return to " +
      "to the town square. To the west is a small " +
      "medical clinic, which offers minimal but " +
      "useful medical services.");
   set_exits(([
      "south" : DIR + "/rooms/town/casino.c",
      "east" : DIR + "/rooms/town/self_storage.c",
      "west" : DIR + "/rooms/town/clinic.c"
   ]));
}
