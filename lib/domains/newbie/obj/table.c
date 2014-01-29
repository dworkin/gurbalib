inherit "std/container";

#include "../domain.h"

void setup(void) {
   set_id("table");
   set_adj("wooden", "small");
   set_short("A small table");
   set_long("A small wooden end table.");

   set_objects(([
      DIR + "/obj/potion":1,
   ]));
}
