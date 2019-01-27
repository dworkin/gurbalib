#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("elf");
   set_short("An elf warrior");
   set_long("He looks very confused. He probably wonders where the wizard he just fought went.");
   set_race("elf");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({
      DIR + "/obj/weapons/heavy_mace.c",
      DIR + "/obj/quest_rings/mithril_ring.c"
   }));
}
