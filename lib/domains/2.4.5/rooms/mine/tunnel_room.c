#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A small room");
   set_long("A small room with rough cut walls.");

   add_exit("south", DIR + "/rooms/tunnel5.c");

   set_objects (([
      DIR + "/monster/hobgoblin.c": 1,
   ]));
}
