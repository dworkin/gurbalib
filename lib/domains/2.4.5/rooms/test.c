#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Computer room");
   set_long("You are in an old computer room.");

   add_exit("east","/domains/2.4.5/rooms/rum2.c");

   set_objects (([
      DIR + "/obj/jacket.c": 1,
   ]));
}

// XXX Need to work on exits, computer and a bunch of other stuff.
