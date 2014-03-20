#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Halfway up the hill on the Isle of the Magi");
   set_long("You are halfway up the hill.  On top of the hill, to the north, " +
      "stands the ruins of the tower of Arcanarton.  Paths wind down to " +
      "the shore of the island to the south, east and west..");

   add_exit("north", DIR + "/rooms/south/sislnd18.c");
   add_exit("south", DIR + "/rooms/south/sislnd7.c");
   add_exit("east", DIR + "/rooms/south/sislnd6.c");
   add_exit("west", DIR + "/rooms/south/sislnd8.c");
}
