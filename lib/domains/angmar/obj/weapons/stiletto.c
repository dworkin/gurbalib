#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   ::setup();
   set_id("stiletto");
   set_short("A stiletto");
   set_long("Ouch! It looks nasty.");

   set_sword_skill("small");
   set_weapon_action("stab");

   set_combat_stats(5, 15, 5);
}
