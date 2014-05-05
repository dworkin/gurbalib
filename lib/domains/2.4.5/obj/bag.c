#include "../domain.h"

inherit "/std/container";

void setup(void) {
   set_id("bag");
   add_id("sack");
   set_adj("large");
   set_short("A large sack");
   set_long("It looks big.");
   set_weight(10);
   set_value(10);
   set_gettable(1);
}
