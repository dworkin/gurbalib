#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("MarketStreet");
   add_area("GurbaOutdoor");

   set_short("Market Street");
   set_long("You are at the eastern end of Market Street, which is " +
      "renowned for both the tenacity of its merchants and the " +
      "shrewdness of its buyers. The business district on both sides " +
      "of the street is one of the oldest sections of town, and here " +
      "you can see the worn brick that signifies the passage of many " +
      "thousands of feet over many years. It is crowded to the point of " +
      "making it extremely difficult to make headway down the road. To " +
      "the east the street opens up into the town square, while in the " +
      "distance to the west sits a large archway.");

   set_exits(([
      "east" : DIR + "/rooms/square_west",
      "west" : DIR + "/rooms/market2",
   ]));
}
