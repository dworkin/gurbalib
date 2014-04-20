#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The ruins of Arcanarton's tower");
   set_long("You are standing among the ruins of the tower of the evil " +
      "mage, Arcanarton.  Legend has it that the tower was destroyed in the " +
      "mage wars about five hundred years ago, when all of the mages of " +
      "Lustria combined their forces and attacked Arcanarton.  " +
      "A great many of them were killed, but they succeeded in destroying " +
      "the evil mage's tower.  His body was never found, and rumors still " +
      "abound that Arcanarton had become a lich and has come back to haunt " +
      "this isle.  The powerful aura of magical combat still hangs in the " +
      "air here.  Lumps of half melted rock lay strewn about, and there is " +
      "very little of the original structure left standing.  To the north " +
      "of the ruins, the hill slopes down to the bridge to the mainland.  " +
      "To the east stands a crumbling monument.  To the west and old, " +
      "disused well.  To the south of the ruins, the hill slopes away, down " +
      "to the edge of Crescent Lake.");

   add_exit("north", DIR + "/rooms/south/sislnd13.c");
   add_exit("south", DIR + "/rooms/south/sislnd16.c");
   add_exit("east", DIR + "/rooms/south/sislnd15.c");
   add_exit("west", DIR + "/rooms/south/sislnd17.c");
}
