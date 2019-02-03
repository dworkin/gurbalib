#include "../../domain.h"

inherit "/std/weapons/blunt";

void setup(void) {
   ::setup();
   set_id("broom");
   set_short("A broom");
   set_long("The broom once belonged to a witch.");

   set_weapon_action("clobber");

   set_combat_stats(1, 5, 1);
}
