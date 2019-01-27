#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
    set_short("The summit of the Noki Cliffs");
    set_long("You have reached the summit of the Noki Cliffs. " +
       "The air is very thin up here. It is not easy to " +
       "to breathe here; you probably should not stay here " +
       "for long if you wish to not suffocate.");

    set_exits(([ "down" : NOKICLIFFS_BASE_CAMP ]));
}

