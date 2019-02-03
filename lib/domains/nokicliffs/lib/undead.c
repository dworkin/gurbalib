#include "../domain.h"

inherit "/std/monster";

int is_undead(void) {
   return 1;
}

void create(void) {
   ::create();
   set_race("undead");
   add_vulnerability("holy");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 3);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 6);
}

