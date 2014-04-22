#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("At the bottom of the Noki Cliffs.");
   set_long("You are the bottom of the Noki Cliffs " +
		"which rise high over head and disappear into the "+
		"cloud. If you are careful you can climb up the "+
		"cliffs from here. A mountain path snakes off to "+
		"the west from here.");

   set_exits(([
    "up" : DIR + "/rooms/cliffs/ledge",
    "west" : DIR + "/rooms/cliffs/path"
   ]));
}

