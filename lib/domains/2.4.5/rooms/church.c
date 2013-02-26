inherit ROOM;

#include "../domain.h"
#include "el.h"

object el;


void setup(void) {
   add_area("2.4.5");

   set_short("Village church");
   set_long("You are in the local village church.  There is a huge " +
      "pit in the center, and a door in the west wall.  " +
      "There is a button beside the door.  This church has the service " +
      "of reviving ghosts.  Dead people come to the church and pray.  " +
      "there is a clock on the wall.  There is an exit to the south.");

   add_exit("north", DIR + "/rooms/vill_shore.c");
   add_exit("south", DIR + "/rooms/vill_green.c");

   add_item("clock","The clock appears to be broken, it is stuck at: 1:26");
   add_item("pit","In the middle of the church is a deep pit.  IT was used " +
      "for sacrifice in the old times, but nowadays it is only " +
      "left for tourists to look at.");

   el = get_el();
   if (el->query_location() == 3) {
      el_arrives();
   } else {
      el_leaves();
   }
}

/* XXX Lots of work needed... */
