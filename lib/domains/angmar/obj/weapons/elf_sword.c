#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   ::setup();
   add_id("elf sword");
   set_short("An elf sword");
   set_long("The king of the elves' sword. It looks very sharp.");

   set_combat_stats(5, 20, 5);
}
