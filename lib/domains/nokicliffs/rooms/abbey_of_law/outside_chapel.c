#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Outside the chapel of the Abbey of Law");
   set_long("You are standing outside of the abbey's chapel. " +
      "To the north is the abbot's dorm room, the door which has " +
      "been ripped off from its hinges and is nowhere to be " +
      "seen. The chapel is to the east.");

   set_exits(([
      "north": DIR + "/rooms/abbey_of_law/abbots_dorm.c",
      "east": DIR + "/rooms/abbey_of_law/chapel.c",
      "west": DIR + "/rooms/abbey_of_law/hallway.c"
   ]));

   set_objects(DIR + "/monsters/monk.c");
}
