#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of the Isle of the Magi");
   set_long("You are standing on the shore of the isle of the Magi.  " +
      "The shore of the island continues northeast and southwest from here.  " +
      "To the northwest, a hill rises up to the ancient ruins of the Tower " +
      "of Arcanarton, the archmage who used to live on this island.  " +
      "To the north you can see some sort of crumbled monument.");

   add_exit("west", DIR + "/rooms/south/sislnd16.c");
   add_exit("northeast", DIR + "/rooms/south/sislnd5.c");
   add_exit("southwest", DIR + "/rooms/south/sislnd7.c");
}
