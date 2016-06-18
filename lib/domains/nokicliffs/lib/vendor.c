#include "../domain.h"

inherit "/std/vendor";

void create(void) {
   ::create();
   set_restock_delay(7200);
   set_will_buy(1);
}
