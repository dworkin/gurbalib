#include "../../domain.h"

inherit "/std/weapons/blunt";

void setup(void) {
   ::setup();
   set_id("oak branch");
   add_id("branch");
   set_short("An oak branch");
   set_long("It seems to be a branch from an oak.");
   set_blunt_skill("large");

   set_weapon_actions(({ "bash", "clobber", "club" }));

   set_combat_stats(4, 8, 1);
}
