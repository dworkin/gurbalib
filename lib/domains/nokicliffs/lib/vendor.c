#include "../domain.h"

inherit "/std/vendor";

void create(void) {
   ::create();
   set_restock_delay(DEFAULT_RESTOCK_DELAY);
   set_will_buy(1);
}
