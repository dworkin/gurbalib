#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("East road");
   set_long("East road runs north-south.  Sun alley is to the west.");

   add_exit("north", DIR + "/rooms/eastroad4.c");
   add_exit("south", DIR + "/rooms/eastroad2.c");
   add_exit("west", DIR + "/rooms/sunalley1.c");
}
