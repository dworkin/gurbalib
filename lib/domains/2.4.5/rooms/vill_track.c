#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Village track");
   set_long("A track going into the village.  The track opens up to a road " +
      "to the east and ends with a green lawn to the west.");

   add_exit("east", DIR + "/rooms/vill_road1.c");
   add_exit("west", DIR + "/rooms/vill_green.c");
}
