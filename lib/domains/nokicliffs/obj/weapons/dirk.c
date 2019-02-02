#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();
   set_id("dirk");
   set_short("A dirk");
   set_adj("");
   set_long("The dirk is particularly use for stabbing people " +
      "in the back. That means it is a favorite weapon of thieves.");
   set_sword_skill("small");
   set_weapon_actions(({
      "stab", "poke", "skewer", "pierce"
   }));
   set_combat_stats(5, 10, 3);
}
