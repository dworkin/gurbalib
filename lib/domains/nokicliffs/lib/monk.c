#include "../domain.h"

inherit DIR + "/lib/monster";

static nomask void clothe(void) {
   equip_monster(({
      NOKICLIFFS_ARMORS_DIR + "/monk_robe",
      NOKICLIFFS_ARMORS_DIR + "/monk_sandals",
      NOKICLIFFS_ARMORS_DIR + "/rope_belt"
   }));
}

void create(void) {
   ::create();
   set_gender("male");
   set_race("human");
   clothe();
}

