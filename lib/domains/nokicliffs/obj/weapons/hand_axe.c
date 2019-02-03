#include "../../domain.h"

inherit DIR + "/lib/axe";

void setup(void) {
   ::setup();

   set_id("axe");
   add_ids("hand axe");
   set_adj("hand");
   set_short("A hand axe");
   set_long("The hand axe is commonly wielded by rangers.");
}
