#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
    ::setup();

    set_short("The summit of the Noki Cliffs.");
    set_long("You have reached the top of the Noki Cliffs. " +
      "The air is very thin up here. It is not easy to " +
      "to here breathe; you probably should not stay here " +
      "for long.");

    set_objects(NOKICLIFFS_MONSTERS_DIR + "/guru.c");
    set_exits(([ "down" : NOKICLIFFS_BASE_CAMP ]));
}

