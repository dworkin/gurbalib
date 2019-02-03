#include "../../domain.h"

inherit "/std/weapons/blunt";

void setup(void) {
   ::setup();
   set_id("stick");
   set_short("A stick");
   set_long("It's a stick. I might work as a weapon in a pinch. But probably not.");
   set_blunt_skill("small");

   set_weapon_actions(({ "rap" }));

   set_combat_stats(1, 2, 1);
}
