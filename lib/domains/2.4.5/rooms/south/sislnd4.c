#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of the Isle of the Magi");
   set_long("You are standing on the shore of the isle of the Magi.  " +
      "The shore of the island continues north and south from here.  " +
      "To the west, a hill rises up to the ancient ruins of the Tower " +
      "of Arcanarton, the archmage who used to live on this island.");

   add_exit("north", DIR + "/rooms/south/sislnd3.c");
   add_exit("south", DIR + "/rooms/south/sislnd5.c");
   add_exit("west", DIR + "/rooms/south/sislnd14.c");
}
