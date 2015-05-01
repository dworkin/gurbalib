#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_combat_stats(1, 3, 0);
   set_adj("short");
   set_short("A short sword");
   set_long("Your standard small sword.");
}

