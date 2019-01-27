#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("tramper");
   set_adj("wandering");
   add_id("wandering tramper");
   set_short("A wandering tramper");
   set_long("The wandering tramper whistles happily.");

   set_race("human");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   set_objects(DIR + "/obj/weapons/stick.c", DIR + "/obj/armors/shoes.c");
}
