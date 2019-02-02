#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("scarecrow");
   set_short("A scarecrow");
   set_long("He is seeing to that nobody steals the corn...");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE * 5);
   set_skill("combat/defense", BASE_DEFENSE);

   equip_monster(({ DIR + "/obj/armors/rubber_boots.c" }));
}
