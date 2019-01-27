#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

void do_extra_actions(void) {
   object cloak;

   cloak = this_object()->present("cloak");
   if (cloak && !cloak->is_cloak_powered()) {
      respond("cloak power on");
   }

   ::do_extra_actions();
}

void setup(void) {
   set_race("catfolk");
   set_name("thief");
   set_short("A thief");
   set_long("The thief who steals valuable things. " +
      "Who disarms traps and stabs people in the back.");

   equip_murder_hobo(({
      NOKICLIFFS_ARMORS_DIR + "/hooded_cloak.c",
      NOKICLIFFS_WEAPONS_DIR + "/kris.c",
      NOKICLIFFS_WEAPONS_DIR + "/dirk.c"
   }), "crown", 2, 2);
}
