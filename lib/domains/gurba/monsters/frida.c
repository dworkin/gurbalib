#include "../domain.h"

inherit "/std/vendor";

void setup(void) {
   set_name("frida");
   set_gender("female");
   add_id("shopkeeper", "merchant");
   set_short("Frida, the florist");
   set_long("She has a long brown pony tail, and a daisy stuck " +
      "behind an ear.");
   set_race("human");
   set_level(15);

   set_restock_delay(7200);
   set_will_buy(1);

   add_item(DIR + "/objects/roses", 9);
}
