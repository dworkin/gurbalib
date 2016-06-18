#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town north square");
   set_long("You are in the northern reaches of the " +
      "town square. Things thin out a little bit here. "+
      "Still, there is plenty to do and see. " +
      "To the north is a smithy's shop and the " +
      "apothecary is to the west. Meanwhile, " +
      "the edge of town is to the east. Beyond the " +
      "town is wilderness.");
   set_exits(([
      "north" : DIR + "/rooms/town/smithy.c",
      "south" : DIR + "/rooms/town/square_middle.c",
      "east" : DIR + "/rooms/town/edge_of_town.c",
      "west" : DIR + "/rooms/town/apothecary.c"
   ]));
}

