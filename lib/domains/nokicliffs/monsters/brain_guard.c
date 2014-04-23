#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("guard");
   set_gender("male");
   set_short("Brain's guard");
   set_long("The brain's guard. He is a hulking beast with a " +
      "permanent demonic snarl revealing disgusting brown " +
      "teeth. Protruding from his forehead are two large " +
      "gently curved horns. His skin is a deep blood red " +
      "colour. He is clearly not pleased by your " +
      "presence here so close to his master, the brain.");
   set_race("demon");
   set_level(40);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 90);
   set_skill("combat/defense", 200);

   set_spell_chance(50);
   set_spell_damage(30);
   set_spell_message("Guard casts a lightning bolt at $t.\n");
}

void create() {
   ::create();
	setup();
}

void announce_yourself() {
   respond("say I have arrived, master.");
   respond("say My life for my master.");
   respond("bow");
}
