#include "../domain.h"

inherit "/std/monster";

void create(void) {
   ::create();
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_skill("combat/unarmed", NOKICLIFFS_UNARMED);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
}
