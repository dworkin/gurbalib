#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorlandAve");
   add_area("GurbaOutdoor");

   set_short("Borland Avenue");
   set_long("The middle of Borland Avenue is surprisingly peaceful. " +
      "Small houses sit on either side of the road and the barking of " +
      "dogs can be heard in the distance. To the south of here lies the " +
      "town square, and to the north sits an intersection.");

   set_exits(([
      "south" : DIR + "/rooms/borland1",
      "north" : DIR + "/rooms/borland3",
   ]));
}
