inherit ROOM;

#include "../domain.h"
#include "el.h"

object el;

void setup(void) {
   add_area("2.4.5");

   set_brief("Wizards hall");
   set_long("You are in the hall of wizards.  There is a door to " +
      "the west, with a button next to it, and a shimmering field to " +
      "the north.");

   set_objects (([
      DIR + "/monsters/leo.c": 1,
   ]));

   el = get_el();
   if (el->query_location() == 3) {
      el_arrives();
   } else {
      el_leaves();
   }
}

/* XXX Need to do the lamp, button, elevator and exits... */
