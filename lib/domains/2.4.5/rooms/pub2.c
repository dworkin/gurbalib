#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_short("The local pub");
   set_long("You can order drinks here.");

   set_objects(([
      DIR + "/monsters/barkeep.c": 1,
      "/domains/required/objects/mer_sign.c": 1,
   }

   add_exit("west", DIR + "/rooms/yard.c");
}

