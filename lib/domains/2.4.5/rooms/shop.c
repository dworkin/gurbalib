#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shop");
   set_long("You are in a shop.  You can buy or sell things here.  " +
      "There is an opening to the north and a small room to the west.");

   add_exit("north", DIR + "/rooms/store.c");
   add_exit("south", DIR + "/rooms/vill_road2.c");
   add_exit("west", DIR + "/rooms/storage.c");

  set_objects(
      DIR + "/monsters/shopkeep.c",
      "/domains/required/objects/mer_sign.c",
      DIR + "/obj/field.c"
   );
}
