#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The local pub");
   set_long("You can order drinks here.");

   set_objects(
      DIR + "/monsters/barkeep.c",
      "/domains/required/objects/mer_sign.c"
   );

   add_exit("west", DIR + "/rooms/yard.c");
}

