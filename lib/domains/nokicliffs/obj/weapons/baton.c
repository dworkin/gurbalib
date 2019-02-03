#include "../../domain.h"

inherit DIR + "/lib/blunt";

void setup(void) {
   ::setup();

   set_id("baton");
   set_short("A baton");
   set_long("The baton has a Noki Town bank emblem " +
            "engraved on it. It is the standard issue weapon " +
            "for the bank guards.");
   set_combat_stats(5, 10, 5);
}

