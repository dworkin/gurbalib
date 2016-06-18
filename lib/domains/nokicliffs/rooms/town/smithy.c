#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town smithy");
   set_long("You are in the Noki Town smithy. The folks " +
      "who run this place are excellent smiths. They not " +
      "create things to sell, but they can also upgrade " +
      "your current adventuring gear. The sounds of metal " +
      "working in the back room fill the smithy's place.");
   set_exits(([ "south" : DIR + "/rooms/town/square_north.c" ]));
}

