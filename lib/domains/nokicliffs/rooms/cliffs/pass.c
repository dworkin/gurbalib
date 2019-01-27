#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A pass in the Noki Cliffs");
   set_long("You are on a pass in the Noki Cliffs. " +
      "The terrain is very steep here, better to watch " +
      "your step. The winds blow through the pass " +
      "with some ferocity. Go west to get out of here; " +
      "go up and over the pass.");

   set_exits(([
      "west" : DIR + "/rooms/cliffs/pass_bottom.c",
      "up" : DIR + "/rooms/cliffs/pass_top.c"
   ]));
}
