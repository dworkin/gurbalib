#include "../../domain.h"

inherit DIR + "/lib/axe";

void setup(void) {
   ::setup();

   set_id("axe");
   add_ids("battle axe", "two-handed battle axe", "two-handed axe");
   set_short("A two-handed battle axe");
   set_long("The blade of this two-handed battle axe has seen " +
      "better days, but do not be fooled as it will still get " +
      "the job done.");
   set_wield_type("dual");
   set_axe_skill("large");
}
