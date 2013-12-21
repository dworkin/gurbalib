#include "../domain.h"

inherit "/std/vendor";

void setup(void) {
   set_name("bogus");
   set_gender("male");
   add_id("shopkeeper", "merchant");
   set_short("Bogus, the merchant");
   set_long("He is a bit overweight, and he oozes money.");
   set_race("human");
   set_level(14);

   set_restock_delay(7200);

   add_item(DIR + "/objects/rock", 9);
   add_item(DIR + "/objects/boots", 5);
   add_item(DIR + "/objects/gloves", 6);
   add_item(DIR + "/objects/hat", 3);
   add_item(DIR + "/objects/jacket", 2);
   add_item(DIR + "/objects/tshirt", 1);
   add_item(DIR + "/objects/sword", 8);
}
