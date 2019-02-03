#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("troll");
   add_ids("forest king", "troll king", "troll king of Darkwood");
   set_short("The troll king of Darkwood");
   set_long("He is an old troll, at least a thousand years old.");
   set_gender("male");
   set_level(20);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE * 3);
   set_skill("combat/defense", BASE_DEFENSE * 5);

   equip_monster(({
      DIR + "/obj/armors/troll_cloak.c"
   }));
}
