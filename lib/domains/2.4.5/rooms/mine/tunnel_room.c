#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A small room");
   set_long("A small room with rough cut walls.");

   add_exit("south", DIR + "/rooms/mine/tunnel5.c");

   set_objects (DIR + "/monsters/hobgoblin.c");
}
