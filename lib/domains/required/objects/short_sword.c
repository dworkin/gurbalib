#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_combat_stats(1, 3, 0);
   set_id("sword");
   set_adj("short");
   set_short("A short sword");
   set_long("Your standard small sword.");

   set_value(30);
   set_size(2);
   set_weight(2);
}

