#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("The general store");
   set_long("Still under contstruction.");

   set_exits(([
      "east" : DIR + "/rooms/infront_store.c", 
   ]));

}
