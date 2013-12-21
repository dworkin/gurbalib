#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("WellerAve");
   add_area("GurbaOutdoor");

   set_short("Weller Avenue");
   set_long("This is the center of Weller Avenue, without a doubt one of " +
      "the more classy sections of town. Tall and ancient trees spread " +
      "their branches high above the road, giving it plenty of shade. To " +
      "the east a charming old house seems to have a somewhat taller fence " +
      "than one might expect, and an ornate iron gate. The avenue " +
      "continues to the north and south. The town square lies to the " +
      "north of here.");

   set_exits(([
      "north" : DIR + "/rooms/weller1",
      "south" : DIR + "/rooms/weller3",
   ]));
}
