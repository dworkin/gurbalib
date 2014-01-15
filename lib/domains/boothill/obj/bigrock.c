#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("rock");
   set_adj("big");
   set_short("A big rock");
   set_long("This rock takes up half of the room.  While the walls " +
      "have been chipped away with axes, this thing doesn't even have a " +
      "scratch on it.  It looks like you would need an elephant or two to " +
      "move it.");
}

