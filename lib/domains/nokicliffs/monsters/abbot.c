#include "../domain.h"

inherit DIR + "/lib/undead";

void setup() {
	::setup();
   set_name("abbot");
   set_gender("male");
   set_short("The Abbot (undead)");
   set_long("The brain's guard. He is a hulking beast with a " +
      "permanent demonic snarl revealing disgusting brown " +
      "teeth. Protruding from his forehead are two large " +
      "gently curved horns. His skin is a deep blood red " +
      "colour. He is clearly not pleased by your " +
      "presence here so close to his master, the brain.");
   set_level(40);
   set_skill("combat/defense", 200);
	set_skill("combat/unarmed", 200);
}

