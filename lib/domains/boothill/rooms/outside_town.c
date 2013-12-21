#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("A prairie");
   set_long("The prairie is lush and green.  It extends to the west.  " +
      "To the east you see a road.");

   set_exits(([
      "east" : DIR + "/rooms/entrance.c", 
      "west" : STARTING_ROOM,
   ]));
}
