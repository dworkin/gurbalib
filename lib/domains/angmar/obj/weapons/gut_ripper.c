#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   set_id("gut ripper");
   add_id("gutripper");
   set_short("The gut ripper");
   set_long("You can only guess what devishly " +
      "deeds this nasty tool was used for. It should serve very well " +
      "as a weapon though.");

   set_weapon_action("rip");
}
