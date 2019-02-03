#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();
   set_id("dagger");
   set_short("A dagger");
   set_adj("simple");
   set_long("A simple dagger for the unenthusiastic combatant.");
   set_sword_skill("small");
   set_combat_stats(5, 10, 3);
}
