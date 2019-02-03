#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("corn cob");
   add_ids("corncob", "cob");
   set_short("A corn cob");
   set_long("A rattly little corn cob. You wouldn't want to eat it.");
   set_weight(1);
   set_value(0);
   set_gettable(1);
}
