#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("On the ledge in the Noki Cliffs");
   set_long("You are standing on a narrow ledge of the " +
      "Noki Cliffs. The drop off is steep and looks like " +
      "a fatal fall. However, you can manage to go west " +
      "from here with sure feet; to the west there looks " +
      "to be a cave entrance which burrows into the cliff face.");

   set_exits(([
      "down" : DIR + "/rooms/cliffs/cliff_bottom.c",
      "west" : DIR + "/rooms/cliffs/cave/cave_start.c"
   ]));
}
