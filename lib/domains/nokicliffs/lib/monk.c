#include "../domain.h"

inherit "/std/monster";

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
   set_level(5);
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
   clothe();
}

