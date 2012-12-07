#include "../domain.h"
inherit ROOM;
int lamp_is_lit;

void setup(void) {
   add_area("2.4.5");

   set_brief("The attic");
}

string query_long() {
   string str;

   str = "This is the attic above the church.  There is a door to the west.";
   if (lamp_is_lit) {
      str += "  The lamp beside the elevator is lit.";
   } else {
      str += "  There is a lamp beside the elevator.";
   }

   return str;
}

/* XXX More work to do... */
