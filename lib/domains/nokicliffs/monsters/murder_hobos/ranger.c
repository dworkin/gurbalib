#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

void setup(void) {
   set_race("elf");
   set_name("ranger");
   set_short("A ranger");
   set_long("The ranger is the party's scout and is completely at home " +
      "in the wilderness.");

   equip_murder_hobo(({
      NOKICLIFFS_ARMORS_DIR + "/leather.c",
      NOKICLIFFS_ARMORS_DIR + "/round_shield.c",
      NOKICLIFFS_WEAPONS_DIR + "/hand_axe.c"
   }));
}
