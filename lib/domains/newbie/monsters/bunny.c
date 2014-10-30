#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("bunny");
   add_adj("fluffy");
   set_short("A fluffy little bunny");
   set_long("It doesn't look like much of a challenge.");
   set_race("rodent");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 20);
   set_skill("combat/defense", 20);
}
