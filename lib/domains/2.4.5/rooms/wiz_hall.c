#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Wizards hall");
   set_long("You are in the hall of wizards.  There is a door to the west " +
      "and a shimmering field to the north.");

   set_objects (([
      DIR + "/monsters/leo.c": 1,
   ]));
}

/* XXX Need to do the lamp, elevator and exits... */
