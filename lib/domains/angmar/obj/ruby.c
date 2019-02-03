#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("ruby");
   add_ids("small ruby");
   set_adj("small");
   set_short("A small ruby");
   set_long("It's quite small as rubies go but it'll probably fetch a few ducats.");
   set_gettable(1);
   set_value(75 + random(50));
   set_weight(1);
}
