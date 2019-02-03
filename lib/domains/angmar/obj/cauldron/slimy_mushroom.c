#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("slimy mushroom");
   add_ids("mushroom");
   set_adj("slimy");
   set_short("A slimy mushroom");
   set_long("Yuck! Disgusting!");
   set_weight(1);
   set_value(0);
   set_gettable(1);
}
