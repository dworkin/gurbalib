#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("troll");
   add_ids("forest king", "troll king", "troll king of Darkwood");
   set_short("The troll king of Darkwood");
   set_long("He is an old troll, at least a thousand years old.");
   set_gender("male");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({
      DIR + "/obj/armors/troll_cloak.c"
   }));
}
