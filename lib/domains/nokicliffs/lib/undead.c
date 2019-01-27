#include "../domain.h"

inherit DIR + "/lib/monster";

int is_undead(void) {
   return 1;
}

void create(void) {
   ::create();
   set_race("undead");
   add_vulnerability("holy");
}

