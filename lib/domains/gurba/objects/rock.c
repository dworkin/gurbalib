#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("rock");
   set_adj("grey");
   set_short("A rock");
   set_long("A pretty boring grey rock.");
   set_gettable(1);
   set_weight(5);
}
