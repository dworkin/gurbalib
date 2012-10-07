#include "../domain.h"
inherit M_VENDOR;

void setup(void) {
   set_name("bogus");
   set_gender("male");
   add_id("shopkeeper", "merchant");
   set_in_room_desc("Bogus, the merchant");
   set_long("He is a bit overweight, and he oozes money.");
   set_race("human");
   set_level(14);

   set_restock_delay(7200);

   add_item(DIR + "/objects/rock", 9);
   add_item(DIR + "/objects/clothing/boots", 5);
   add_item(DIR + "/objects/clothing/gloves", 6);
   add_item(DIR + "/objects/clothing/hat", 3);
   add_item(DIR + "/objects/clothing/jacket", 2);
   add_item(DIR + "/objects/clothing/tshirt", 1);
   add_item(DIR + "/objects/weapons/sword", 8);
}
