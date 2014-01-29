#include "../domain.h"
#include "el.h"

inherit "/std/room";

int lamp_is_lit;
object el;

void setup(void) {
   add_area("2.4.5");

   set_short("The attic");

   add_action("press_button", "press");
   add_action("press_button", "push");

   el = get_el();
   if (el) {
      if (el->query_location() == 3) {
         el_arrives();
      } else {
         el_leaves();
      }
   }
}

string query_long() {
   string str;

   str = "This is the attic above the church.  There is a door to the west," +
      "with a button next to it.";
   if (lamp_is_lit) {
      str += "  The lamp beside the elevator is lit.";
   } else {
      str += "  There is a lamp beside the elevator.";
   }

   return str;
}

/* XXX More work to do... */
