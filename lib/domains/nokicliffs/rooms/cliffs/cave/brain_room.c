#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();
   set_short("A large cave chamber in the Noki Cliffs.");
   set_long("");
   set_objects(NOKICLIFFS_BRAIN);
	set_exits((["south":DIR + "/rooms/cliffs/cave/puzzle_chamber.c"]));
}
