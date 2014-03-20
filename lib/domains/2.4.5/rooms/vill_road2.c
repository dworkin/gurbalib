#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Village road");
   set_long("A long road going east through the village.  There are " +
     "stairs going down.  The road continues to the west.  " +
     "To the north is the shop, and to the south is the adventurers " +
     "guild.  The road runs towards the shore to the east.");

   add_exit("north", DIR + "/rooms/shop.c");
   add_exit("south", DIR + "/rooms/adv_guild.c");
   add_exit("east", DIR + "/rooms/vill_shore.c");
   add_exit("west", DIR + "/rooms/vill_road1.c");
   add_exit("down", DIR + "/rooms/station.c");

   set_objects (DIR + "/monsters/harry.c");
}

