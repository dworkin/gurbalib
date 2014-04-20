#include "../domain.h"

inherit "/std/container";

void setup(void) {
   set_id("chest");
   set_short("A chest");
   set_long("A chest that seems to be of a high value.");
   set_weight(10);
   set_internal_max_weight(1000);
   set_gettable(1);
   set_value(200);
}

