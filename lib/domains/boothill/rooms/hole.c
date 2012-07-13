#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("A crudely dug hole");
   set_long("Your average hole in the ground.");

   set_exits(([
      "up" : DIR + "/rooms/boothill.c", 
   ]));
}
