#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();

   set_id("claymore");
   set_adj("two-handed");
   add_ids("two-handed claymore");
   set_short("A two-handed claymore");
   set_long("This two-handed claymore has seen much use, " +
            "but is in wonderful fighting condition.");
   set_wield_type("dual");
   set_sword_skill("large");
}
