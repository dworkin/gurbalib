#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A small grove on the shore of the Island of the Magi");
   set_long("You are standing in a small grove on the shore of the Isle of " +
      "the Magi.  All of the trees here are either diseased, dead or heavily " +
      "mutated.  The shoreline continues southeast from here, as well as " +
      "heading northwest to Focus Point.  The grove continues to the north.  " +
      "To the east, you can see an old disused well, and beyond that, on " +
      "top of the hill, stands the ruined tower of Arcanarton.");

   add_exit("north", DIR + "/rooms/south/sislnd11.c");
   add_exit("east", DIR + "/rooms/south/sislnd17.c");
   add_exit("southeast", DIR + "/rooms/south/sislnd8.c");
   add_exit("northwest", DIR + "/rooms/south/sislnd10.c");
}
