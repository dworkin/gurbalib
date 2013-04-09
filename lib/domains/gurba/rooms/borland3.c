#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorlandAve");
   add_area("GurbaOutdoor");

   set_short("Borland Avenue");
   set_long("This charming section of street lies at the north end of " +
      "Borland Avenue, which by all accounts seems like quite a pleasant " +
      "place to live. The sun filters through the branches of tall trees " +
      "and children can be heard playing in the distance. To the north " +
      "Borland Avenue meets with the Border Walk, and to the south it " +
      "heads toward the town square.");

   set_exits(([
      "south" : DIR + "/rooms/borland2",
      "north" : DIR + "/rooms/border_borland",
   ]));
}
