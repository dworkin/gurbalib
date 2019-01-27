#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("scarecrow");
   set_short("A scarecrow");
   set_long("He is seeing to that nobody steals the corn...");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({ DIR + "/armors/rubber_boots.c" }));
}
