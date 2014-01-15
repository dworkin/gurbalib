#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("rubble");
   set_short("A pile of rubble");
   set_long("A large pile of rubble strewn about the room.  It looks " +
      "like it will take quite a lot of time to clean this mess up.");
}
