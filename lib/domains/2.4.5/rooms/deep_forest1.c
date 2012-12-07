#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Deep forest");
   set_long("In the deep forest.  The wood lights up to the east.");

   add_exit("north", DIR + "/rooms/plain12.c");
}
