#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("staff");
   set_adj("large");
   set_short("A golden staff");
   set_long("A Large golden staff.  You better not use it, it looks valuable.");
   set_gettable(1);

   set_value(300);
   set_weight(10);
}
