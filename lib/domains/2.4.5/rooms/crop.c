#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Fields");
   set_long("You are in the middle of the fields where the city grows " +
      "all its crops.  A road runs north of here.  A large, dark castle " +
      "lies to the south beyond the fields.");

   add_item("fields", "Crops and a castle beyond.");
   add_item("crops", "There are all kinds of crops grown for the city.");
   add_item("road", "The road goes north.");
   add_item("castle", "Perhaps you should go south for a closer look.");

   add_exit("north", DIR + "/rooms/vill_shore.c");
   add_exit("south", "/domains/angmar/rooms/area_entrance.c");
}
