#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("witch");
   set_short("A witch");
   set_long("The witches are not to be tampered with...");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({ DIR + "/obj/weapons/broom.c" }));
}
