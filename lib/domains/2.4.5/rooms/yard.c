#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Small yard");
   set_long("A small yard surrounded by houses.");

   add_exit("south", DIR + "/rooms/vill_road1.c");
   add_exit("east", DIR + "/rooms/pub2.c");

   set_objects (
      DIR + "/monsters/beggar.c",
      DIR + "/obj/knife.c"
    );
}
