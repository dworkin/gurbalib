#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town outskirts");
   set_long("You are just outside of Noki Town in the "+
      "wilderness. The village lies to the west. " +
      "Enjoy the sounds of the birds.");
   set_exits(([
      "west" : DIR + "/rooms/town/edge_of_town.c"
   ]));
}

