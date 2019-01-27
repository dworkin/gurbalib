#include "../domain.h"

inherit DIR + "/lib/monster";

void setup(void) {
   set_name("guard");
   add_id("brain guard");
   set_gender("male");
   set_short("Brain's guard");
   set_long("The brain's guard. He is a hulking beast with a " +
      "permanent demonic snarl revealing disgusting brown " +
      "teeth. Protruding from his forehead are two large " +
      "slightly curved horns. His skin is a deep blood red " +
      "color. He is clearly not pleased by your " +
      "presence here so close to his master, the brain.");
   set_race("demon");

   set_spell_chance(50);
   set_spell_damage(30);
   set_spell_message("Guard casts a lightning bolt at $t.\n");
}

void announce_yourself(void) {
   respond("say I have arrived, master.");
   respond("say My life for my master.");
   respond("bow");
}

void random_act_of_menace(void) {
   respond("growl");
}

