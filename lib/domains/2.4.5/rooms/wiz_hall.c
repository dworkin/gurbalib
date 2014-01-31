inherit "/std/room";

#include "../domain.h"
#include "el.h"

object el;

void setup(void) {
   add_area("2.4.5");

   set_short("Wizards hall");
   set_long("You are in the hall of wizards.  There is a door to " +
      "the west, with a button next to it, and a shimmering field to " +
      "the north.");

   add_action("press_button", "press");
   add_action("press_button", "push");

   set_objects (([
      DIR + "/monsters/leo.c": 1,
   ]));

   el = get_el();
   if (el) {
      if (el->query_location() == 1) {
         el_arrives();
      } else {
         el_leaves();
      }
   }
}

int query_floor() {
   return 1;
}

/* XXX Need to do the lamp, button, elevator and exits, here, attic and church
*/
