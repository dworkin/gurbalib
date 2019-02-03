#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   ::setup();
   set_adj("small");
   add_id("small sword");
   set_short("A small sword");
   set_long("It is small, as swords go.");

   set_weapon_action("cut");
   set_sword_skill("small");

   set_combat_stats(5, 15, 5);
}