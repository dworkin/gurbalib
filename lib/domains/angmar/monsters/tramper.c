#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("tramper");
   set_adj("wandering");
   add_id("wandering tramper");
   set_short("A wandering tramper");
   set_long("The wandering tramper whistles happily.");

   set_race("human");
   set_level(1);
   set_hit_skill("combat/blunt/small");
   set_skill("combat/blunt/small", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);

   set_objects(DIR + "/obj/weapons/stick.c", DIR + "/obj/armors/shoes.c");
}
