#include "../domain.h"

inherit "/std/object";

void setup(void) {

   set_id("stone");
   set_short("A black stone");
   set_long("A small black stone.  It looks like it might be valuable.");
   set_gettable(1);
   set_value(60);
   set_weight(1);
}
