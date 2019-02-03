#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("spirit");
   set_adj("evil powerful");
   set_short("An evil powerful spirit");
   set_long("Get out of here! It will kill you!");
   set_level(20);
   set_aggressive(1);
   set_hit_skill("combat/edge/large");
   set_skill("combat/edge/large", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE * 8);

   equip_monster(({ DIR + "/obj/weapons/doomsgiver.c" }));

   set_spell_chance(30);
   set_spell_damage(3);
   set_spell_message("The spirit a fire elemental at $t.");
}
