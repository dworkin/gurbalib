#include "../domain.h"

inherit DIR + "/lib/undead";

int is_vampire(void) {
   return 1;
}

void create(void) {
   ::create();
   set_race("vampire");
   add_bane("garlic");
   add_vulnerability("silver");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 4);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 8);
}

