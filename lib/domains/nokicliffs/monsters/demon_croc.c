#include "../domain.h"

inherit "/std/monster";

void targeted_action(string msg, object target, varargs mixed objs ...) {
   if (msg == "$N $vfall to the ground...dead.") {
      msg = "$N $vroll belly up and floats on the water...dead.";
   }
   ::targeted_action(msg, target, objs);
}

void setup(void) {
   set_name("demon croc");
   add_id("demon", "croc", "crocodile", "demon crocodile");
   set_short("A demon crocodile");
   set_long("It has terribly sharp teeth and a monstrously " +
      "strong bite. And it is hungry.");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 3);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 5);
   set_race("demon");
   set_aggressive(1);
   set_hit_string("bite");

   equip_monster(({ TWOFOURFIVE_DIR + "/obj/gem.c" }));
}
