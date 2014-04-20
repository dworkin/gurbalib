#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Dead end");
   set_long("Another dead end.");

   add_exit("west", DIR + "/rooms/mine/tunnel28.c");

   set_objects (DIR + "/monsters/dragon.c");
}
