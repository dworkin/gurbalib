#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("dead fish");
   set_adj("dead");
   add_id("fish");
   set_short("A dead fish");
   set_long("It smells.");
   set_weight(1);
   set_value(0);
   set_gettable(1);
}
