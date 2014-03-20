#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Road");
   set_long("You are on a road going out of the village. Eastroad runs " +
      "north from here, along the eastern perimeter of the city, and to " +
      "the south are some fields planted with all the crops that the " +
      "city needs. The main road runs towards the shore to the east, " +
      "and into the city to the west.");

   add_exit("north", DIR + "/rooms/eastroad1.c");
   add_exit("south", DIR + "/rooms/crop.c");
   add_exit("east", DIR + "/rooms/jetty.c");
   add_exit("west", DIR + "/rooms/vill_road2.c");
}
