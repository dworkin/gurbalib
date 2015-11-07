#include "../domain.h"

inherit "/std/vendor";

void setup(void) {
   set_name("barkeeper");
   add_ids("barkeep", "lazyeye", "shopkeeper", "merchant");
   set_gender("male");
   set_short("Lazyeye, the barkeeper");
   set_long("He really doesn't like people staring at him.");
   set_race("human");
   set_level(15);

   set_restock_delay(7200);
   set_will_buy(1);

   add_item(DIR + "/obj/classbeer", 20);
   add_item(DIR + "/obj/special", 10);
   add_item(DIR + "/obj/firebreath", 10);
}
