#include "../domain.h"

inherit "/std/monster";
inherit DIR + "/lib/simple_block";

void setup(void) {
   set_name("doom queen");
   add_ids("queen of doom", "queen");
   set_short("The queen of doom");
   set_long("This is the queen of doom. " +
      "Killing her is the only way to save yourself.");
   set_race("monster");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 3);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 5);
   set_spell_chance(50);
   set_spell_damage(1);
   set_spell_message("The doom queen blasts $t with a bolt of doom.\n");
   add_block("up");
}
