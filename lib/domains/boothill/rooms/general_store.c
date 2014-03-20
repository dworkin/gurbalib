#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("The general store");
   set_long("This quaint little shop has all of the basic necessities. " +
      "Here in the wild west, if you can't get it at the general store, " +
      "your probably going to have to wait months to get a package.  " +
      "While looking around at the sundry goods, you smell something " +
      "delicious.");

   set_exits(([
      "east" : DIR + "/rooms/infront_store.c", 
   ]));

   set_objects(
      DIR + "/monsters/will",
      "/domains/required/objects/mer_sign"
   );
}
