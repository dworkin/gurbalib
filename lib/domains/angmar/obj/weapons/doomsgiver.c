#include "../../domain.h"

inherit "/std/weapons/sword";
inherit "/std/modules/m_readable";

void setup(void) {
   ::setup();
   set_id("doomsgiver");
   set_short("The Doomsgiver");
   set_long("This is a very powerful sword. You feel a magic aura surrounding it. " +
            "There is something written on it.");
   set_message("The language is very old. You can hardly understand it. But the " +
               "sword once seem to have been owned by Angmar himself.");

   set_weapon_action("slice");
   set_sword_skill("large");

   set_combat_stats(5, 23, 8);
}
