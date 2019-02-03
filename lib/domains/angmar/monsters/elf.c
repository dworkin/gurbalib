#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("elf");
   set_short("An elf");
   set_long("An elf, ready for combat.");
   set_race("elf");
   set_level(10);
   set_hit_skill("combat/edge/small");
   set_skill("combat/edge/small", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);

   equip_monster(({
      DIR + "/obj/weapons/big_knife.c",
      DIR + "/obj/weapons/small_sword.c"
   }));
}
