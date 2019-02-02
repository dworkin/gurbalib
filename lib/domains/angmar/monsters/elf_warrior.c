#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("elf");
   set_short("An elf warrior");
   set_long("He looks very confused. He probably wonders where the wizard he just fought went.");
   set_race("elf");
   set_level(15);
   set_hit_skill("combat/blunt/large");
   set_skill("combat/blunt/large", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE * 5);

   equip_monster(({
      DIR + "/obj/weapons/heavy_mace.c",
      DIR + "/obj/quest_rings/mithril_ring.c"
   }));
}
