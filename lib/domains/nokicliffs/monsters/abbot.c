#include "../domain.h"

inherit DIR + "/lib/monk";

void setup(void) {
   set_name("abbot");
   set_short("The Abbot");
   set_long("The abbey's abbot. He is an older man, slightly " +
      "hunched. He is balding with a crescent of pure white hair " +
      "around the back of his head. He wears an old robe secured " +
      "with a simple rope. Upon his feet he wears sandals.");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
}

