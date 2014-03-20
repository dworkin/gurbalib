#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The orc valley");
   set_long("You are in the orc valley.  This place is inhabited by orcs.  " +
      "There is a fortress to the north, with many signs of orcs.");
   add_exit("north", DIR + "/rooms/fortress.c");
   add_exit("east", DIR + "/rooms/slope.c");

   set_objects (DIR + "/monsters/orc.c");
}
