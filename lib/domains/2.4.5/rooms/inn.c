#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("East Road Inn Inn");
   set_long("You are in the East Road Inn.  Here you can buy food to still " +
      "your hunger, but only a limited selection is available.");

   set_objects(
        DIR + "/monsters/innkeep.c",
        "/domains/required/objects/mer_sign.c"
   );

   add_exit("east", DIR + "/rooms/eastroad5.c");
}
