#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("garlic");
   set_short("A garlic clove");
   set_long("A garlic clove. It has a strong garlic smell coming from it.");
   set_gettable(1);
   set_value(5);
   set_weight(1);
   add_bane("garlic"); /* XXX is this correct? forgot how these work! */
}

