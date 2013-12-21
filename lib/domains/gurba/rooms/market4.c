#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("MarketStreet");
   add_area("GurbaOutdoor");

   set_short("Market Street");
   set_long("This is the western end of Market Street, an extremely " +
      "old and narrow road that is known for having some of the best " +
      "deals on all manner of goods. Naturally, the combination has " +
      "led to a bit of a congestion problem. All around you people " +
      "push and shove while trying to haggle with any of a hundred " +
      "merchants, or simply trying to make headway in either " +
      "direction. The western gate can be seen from here, and the " +
      "town square lies in the distance to the east.");

   set_exits(([
      "east" : DIR + "/rooms/market3",
      "west" : DIR + "/rooms/gate_west",
   ]));
}
