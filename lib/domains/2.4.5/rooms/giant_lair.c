#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Lair of the Giant");
   set_long("There are mountains all around you.");

   add_exit("east", DIR + "/rooms/giant_path.c");
   add_exit("west", DIR + "/rooms/giant_conf.c");

   set_objects (([
      DIR + "/monsters/giant.c": 1,
   ]));
}
