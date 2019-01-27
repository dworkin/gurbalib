#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town apothecary");
   set_long("You are in the Noki Town apothecary. " + 
      "Soon you will be able to dry roots here " +
      "as well as buy some other new agey hoodoo. " +
      "Type 'list' to find out what is available.");
   set_exits(([
      "east" : DIR + "/rooms/town/square_north.c"
   ]));
   set_objects(DIR + "/monsters/town/silverspun.c");
}

