#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The meadow");
   set_long("You are standing in the middle of a meadow. " +
      "Many different kinds of flowers are growing here.");

   add_exit("east", FAIRYLAND_ROOMS + "/road3.c");
   add_exit("west", FAIRYLAND_ROOMS + "/ditch.c");

   add_item("meadow", "The grass blows in the wind.");
   add_item("wind", "You lick a finger, and stick it into the wind: North.");
   add_item("flowers", "They smell fresh, as if they had grown here forever.");
}
