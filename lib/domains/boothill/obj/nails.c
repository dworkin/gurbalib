#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("nails");
   add_id("box of nails");
   set_adj("small");
   set_short("A small box of nails");
   set_long("You could do some serious handyman work with these puppies.");
   set_gettable(1);
   set_weight(10);
   set_value(10);
}
