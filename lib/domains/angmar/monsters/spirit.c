#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("witch");
   set_short("A witch");
   set_long("A nasty witch.");
   set_level(1);
   set_aggressive(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({ DIR + "/obj/weapons/broom.c" }));
}
