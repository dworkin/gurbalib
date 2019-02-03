#include "../../domain.h"

inherit "/std/weapon";

void setup(void) {
   ::setup();
   set_id("spear");
   add_id("heavy spear");
   set_short("A heavy spear");
   set_long("It's about six feet long, with a metal head inserted into the tip. " +
		  "Some type of coarse cord is wrapped around the tip to hold the point in " +
		  "the spear. You notice that the middle section of the spear seems worn, " +
		  "as if it were used in many battles.");

   set_weapon_skill("combat/sharp/heavy");

   set_weapon_actions(({
      "jab",
      "impale",
      "stab",
      "pierce"
   }));

   set_combat_stats(5, 25, 5);
}
