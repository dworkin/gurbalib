#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("BorlandAve");
   add_area("GurbaOutdoor");

   set_short("Borland Avenue");
   set_long("This is the south end of Borland Avenue, which runs " +
      "through an active residential district of town. Though not " +
      "quite as upscale as Weller Avenue to the south, it nonetheless " +
      "is well-kept and seems like a nice place to live. The town square " +
      "is south of here, and the avenue continues to the north.");

   set_exits(([
      "south" : DIR + "/rooms/square_north",
      "north" : DIR + "/rooms/borland2",
   ]));
}
