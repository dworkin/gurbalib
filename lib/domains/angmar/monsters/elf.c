#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("elf");
   set_short("An elf");
   set_long("An elf, ready for combat.");
   set_race("elf");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({
      DIR + "/obj/weapons/big_knife.c",
      DIR + "/obj/weapons/small_sword.c"
   }));
}
