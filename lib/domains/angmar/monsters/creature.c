#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("creature");
   set_short("A loathesome creature");
   set_long("A disgusting malformed thing, who perhaps was a human once. " +
      "Angmar was probably in a bad mood when he created this indescribable being. " +
      "Take care!");
   set_level(20);
   set_hit_skill("combat/edge/medium");
   set_skill("combat/edge/medium", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE * 10);

   set_spell_chance(30);
   set_spell_damage(2);
   set_spell_message("The create throws a spell at $t.\n");

   equip_monster(({ DIR + "/obj/weapons/gut_ripper.c" }));
}
