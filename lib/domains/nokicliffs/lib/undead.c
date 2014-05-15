#include "../domain.h"

inherit "/std/monster";

int is_undead() {
   return 1;
}

void setup() {
   set_race("undead");
   add_vulnerability("holy");
}

