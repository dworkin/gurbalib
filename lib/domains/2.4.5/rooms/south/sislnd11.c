#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A grove on the shore of the Isle of the Magi");
   set_long("You are standing in a grove on the shore of the Isle of the " +
      "Magi.  All of the trees here are either diseased, dead or heavily " +
      "mutated.  The shore of the island continues to the east and the " +
      "grove follows the shoreline west to Focus Point.  The grove also " +
      "continues to the south.");

   add_exit("south", DIR + "/rooms/south/sislnd9.c");
   add_exit("east", DIR + "/rooms/south/sislnd12.c");
   add_exit("west", DIR + "/rooms/south/sislnd10.c");
}
