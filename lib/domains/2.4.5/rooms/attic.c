#include "../domain.h"

inherit "/std/room";
inherit "/domains/2.4.5/lib/el";

int lamp_is_lit;
object el;

int query_floor() {
   return 3;
}

void setup(void) {
   add_area("2.4.5");

   set_short("The attic");

   add_action("press_button", "press");
   add_action("press_button", "push");

   el = get_el();
   if (el) {
      if (el->query_location() == query_floor()) {
         el_arrives();
      } else {
         el_leaves();
      }
   }
}

string query_long() {
   string str;

   str = "This is the attic above the church.  There is a door to the west, " +
      "with a button next to it.";
   if (lamp_is_lit == 1) {
      str += "  The lamp beside the elevator is lit.";
   } else {
      str += "  There is a lamp beside the elevator.";
   }

   return str;
}

void lamp_on() {
   lamp_is_lit = 1;
}

void lamp_off() {
   lamp_is_lit = 0;
}

