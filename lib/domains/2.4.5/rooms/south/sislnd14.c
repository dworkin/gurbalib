#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Halfway up the hill on the Isle of the Magi");
   set_long("You are halfway up the hill.  On top of the hill, to the " +
      "southwest, stands the ruins of the tower of Arcanarton, but " +
      "there is no direct route to the top from here.  To the south stands " +
      "some sort of crumbling monument.  A path winds around the hill to " +
      "the west, and heads down to the shore of the island to the north and " +
      "east.");

   add_exit("north", DIR + "/rooms/south/sislnd2.c");
   add_exit("south", DIR + "/rooms/south/sislnd15.c");
   add_exit("east", DIR + "/rooms/south/sislnd4.c");
   add_exit("west", DIR + "/rooms/south/sislnd13.c");
}
