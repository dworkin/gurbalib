#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("cloak");
   add_ids("simple cloak");
   set_adj("simple");
   set_short("A simple cloak");
   set_long("This simple cloak is finely crafted.");
   set_ultra_light();
}
