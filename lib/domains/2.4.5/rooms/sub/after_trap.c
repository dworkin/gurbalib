#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Black room");
   set_long("This is the black room.");

   /* XXX need to do door stuff here */
   add_exit("east", DIR + "/rooms/sub/door_trap.c");

   set_objects (([
      DIR + "/monsters/rat.c": 1,
   ]));
}
