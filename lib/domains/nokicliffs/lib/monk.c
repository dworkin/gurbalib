#include "../domain.h"

inherit "/std/monster";

static nomask void clothe(void) {
   equip_monster(({
      NOKICLIFFS_ARMOURS_DIR + "/monk_robe",
      NOKICLIFFS_ARMOURS_DIR + "/monk_sandals",
      NOKICLIFFS_ARMOURS_DIR + "/rope_belt"
   }));
}

void setup(void) {
   ::setup();
   set_gender("male");
   set_race("human");
   clothe();
}

