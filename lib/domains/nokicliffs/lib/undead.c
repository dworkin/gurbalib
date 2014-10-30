#include "../domain.h"

inherit "/std/monster";

int is_undead(void) {
   return 1;
}

void setup(void) {
   set_race("undead");
   add_vulnerability("holy");
}

