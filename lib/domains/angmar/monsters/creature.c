#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("creature");
   set_short("A loathesome creature");
   set_long("A disgusting malformed thing, who perhaps was a human once. " +
      "Angmar was probably in a bad mood when he created this indescribable being. " +
      "Take care!");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   set_spell_chance(50);
   set_spell_damage(1);
   set_spell_message("The create throws a spell at $t.\n");

   equip_monster(({ DIR + "/obj/weapons/gut_ripper.c" }));
}
