#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   ::setup();
   set_id("gut ripper");
   add_ids("gutripper", "ripper");
   set_short("The gut ripper");
   set_long("You can only guess what devishly " +
      "deeds this nasty tool was used for. It should serve very well " +
      "as a weapon though.");

   set_weapon_action("rip");

   set_combat_stats(5, 22, 5);
}
