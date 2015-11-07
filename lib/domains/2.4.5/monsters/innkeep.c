#include "../domain.h"

inherit "/std/vendor";

void setup(void) {
   set_name("innkeeper");
   add_ids("innkeep", "tom", "shopkeeper", "merchant");
   set_gender("male");
   set_short("Tom, the innkeeper");
   set_long("He is a large healthy man.");
   set_race("human");
   set_level(15);

   set_restock_delay(7200);
   set_will_buy(1);

   add_item(DIR + "/obj/com_meal", 20);
   add_item(DIR + "/obj/mer_meal", 10);
   add_item(DIR + "/obj/ric_meal", 10);
   add_item(DIR + "/obj/mug", 10);
}
