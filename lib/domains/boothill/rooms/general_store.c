#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_short("The general store");
   set_long("Still under contstruction.");

   set_exits(([
      "east" : DIR + "/rooms/infront_store.c", 
   ]));

}
