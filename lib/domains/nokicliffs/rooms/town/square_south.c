#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town south square");
   set_long("You are at the southern end of the Noki " +
      "Town square. To the east is the bank. To the " +
      "west is a self storage service with a public " +
      "bath house.");
   set_exits(([
      "north" : DIR + "/rooms/town/square_middle.c",
      "south" : DIR + "/rooms/town/town_start.c",
      "east" : DIR + "/rooms/town/bank.c",
      "west" : DIR + "/rooms/town/self_storage.c",
   ]));
}

