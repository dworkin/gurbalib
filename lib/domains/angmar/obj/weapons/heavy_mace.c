#include "../../domain.h"

inherit "/std/weapons/blunt";

void setup(void) {
   ::setup();
   set_id("mace");
   set_adj("heavy");
   set_short("A heavy mace");
   set_long("It has fresh bloodstains on it.");

   set_combat_stats(5, 22, 5);
}
