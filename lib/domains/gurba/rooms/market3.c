#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("MarketStreet");
   add_area("GurbaOutdoor");

   set_short("Market Street");
   set_long("You are near the middle of Market Street, the oldest (and " +
      "most crowded) section of Gurba Town. This particular section of " +
      "the street seems to be a bit wider than the surrounding areas, " +
      "thus giving those weary of the oppressive atmosphere a chance to " +
      "catch a bit of fresh air. The buildings here are tall and crooked, " +
      "and merchants are set up all along the road with their wares. The " +
      "town square can barely be seen through the sea of people to the " +
      "east, while the western gate lies in the opposite direction.");

   set_exits(([
      "east" : DIR + "/rooms/market2",
      "west" : DIR + "/rooms/market4",
   ]));
}
