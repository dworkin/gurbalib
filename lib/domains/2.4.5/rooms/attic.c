#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The attic");
   set_long("This is the attic above the church.  " +
      "There is a door to the west.");
}

// XXX More work to do...
