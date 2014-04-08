#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

int count;

void setup() {
   object obj;

   set_name("wyrm");
   set_short("The wyrm of Arcanarton");
   set_long("The giant undead dragon you see before you is the result " +
       "of one of Arcanarton's magic experiments.");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 100);
   set_skill("combat/defense", 100);
   set_level(17);
   set_aggressive(1);

   obj = clone_object(DIR + "/obj/gem");
   obj->setup();
   obj->move(this_object());

   obj = clone_object("/domains/required/objects/coin.c");
   obj->set_amount(random(500) + 1);
   obj->move(this_object());
   obj->setup();

   set_spell_chance(50);
   set_spell_damage(100);
   set_spell_message("Arcanarton's wyrm turns his head and " +
      "breathes death at $t.\n");
}
