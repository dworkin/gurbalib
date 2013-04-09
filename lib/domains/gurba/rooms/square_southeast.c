#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - Southeast");
   set_long("This little area in the southeast part of the square seems " +
      "to have been reserved for a carefully-landscaped flower garden. " +
      "Happy couples and other townspeople wander down the little gravel " +
      "paths that separate the rows of colorful flowers and small trimmed " +
      "bushes. A few clear voices can be heard to the west, while " +
      "intensive commerce appears to be taking place to the north. " +
      "South of the gardens a well-kept armor shop is doing business.");

   set_exits(([
      "west" : DIR + "/rooms/square_south",
      "north" : DIR + "/rooms/square_east",
      "northwest" : DIR + "/rooms/square_center",
      "south" : DIR + "/rooms/armorshop",
   ]));

   add_item("garden", "A great deal of care seems to have gone into the " +
      "layout of the garden.  Colors are arranged in a complementary " +
      "way and charming little paths allow one to walk between the rows " +
      "and enjoy the peaceful atmosphere.");
   add_item("flowers", "There are all kinds of flowers, from roses to " +
      "daisies, arranged in colorful patterns.");
   add_item("bushes", "The bushes have been trimmed into a variety of " +
      "intriguing shapes.");
}
