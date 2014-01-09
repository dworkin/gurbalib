#include "../domain.h"

inherit "/std/light";

void setup(void) {
   set_id("torch");
   set_adj("large");
   set_short("A torch");
   set_long("A stick with some burnable stuff stuck to the end of it.");
   set_gettable(1);

   set_value(1);
   set_weight(10);
   set_fuel(1000);
}

