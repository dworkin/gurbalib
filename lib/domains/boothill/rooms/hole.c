#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("A crudely dug hole");
   set_long("Your average hole in the ground.");
   set_light(0);

   set_exits(([
      "up" : DIR + "/rooms/boothill.c", 
   ]));
}
