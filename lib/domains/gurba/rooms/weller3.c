#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("WellerAve");
   add_area("GurbaOutdoor");

   set_short("Weller Avenue");
   set_long("You stand at the south end of Weller Avenue.  It is a " +
      "pleasant but (judging by the relatively large houses) probably " +
      "expensive place to live. It is also a bit quieter than some other " +
      "parts of town. To the north of here lies the town square, while " +
      "to the south the avenue meets with the Border Walk.");

   set_exits(([
      "north" : DIR + "/rooms/weller2",
      "south" : DIR + "/rooms/border_weller",
   ]));
}
