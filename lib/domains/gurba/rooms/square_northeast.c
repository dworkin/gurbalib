#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - Northeast");
   set_long("Not much seems to be going on here in the northeastern " +
      "corner of the square.  The occasional merchant and street " +
      "performer wanders by, but the real activity seems to be located " +
      "to the south and west of here.  A clothing shop to the east seems " +
      "to be doing fairly steady business.");

   set_exits(([
      "west" : DIR + "/rooms/square_north",
      "south" : DIR + "/rooms/square_east",
      "southwest" : DIR + "/rooms/square_center",
   ]));
}
