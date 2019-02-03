#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("skeleton");
   add_id("rat skeleton");
   set_short("A rat skeleton");
   set_long("A perfectly preseved rat skeleton. The jailer's lunch, perhaps?");
   set_value(0);
   set_weight(1);
   set_gettable(1);
}
