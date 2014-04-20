#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of the Isle of the Magi");
   set_long("You are standing on the shore of the Isle of the " +
      "Magi.  The shore of the island continues northeast to the ruined " +
      "bridge and west into a small grove from here.  To the south is a old, " +
      "disused well.  Standing atop a cliff to the southwest is the ruined " +
      "tower of Arcanarton, but there is no way to get up there from here.  " +
      "A path does lead up the hill to the east though.");

   add_exit("south", DIR + "/rooms/south/sislnd17.c");
   add_exit("east", DIR + "/rooms/south/sislnd13.c");
   add_exit("west", DIR + "/rooms/south/sislnd11.c");
   add_exit("northeast", DIR + "/rooms/south/sislnd1.c");
}
