#include "../domain.h"

inherit "/std/vendor";

void setup(void) {
   set_name("Zalli");
   add_ids("bartender", "bar tender");
   set_gender("female");
   set_short("Zalli, the bar tender");
   set_long("Zalli is a former adventurer starting a new life as " +
      "The Laughing Horse Inn's bar tender.");
   set_race("human");
   set_level(15);

   set_restock_delay(120);
   set_will_buy(0);

   add_item(DIR + "/obj/laughing_horse_inn/beer", 50);
   add_item(DIR + "/obj/laughing_horse_inn/whiskey_on_rocks", 25);
   add_item(DIR + "/obj/laughing_horse_inn/docs_special_mixture", 12);
}
