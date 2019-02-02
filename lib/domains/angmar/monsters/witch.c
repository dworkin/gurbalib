#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("witch");
   set_short("A witch");
   set_long("The witches are not to be tampered with...");
   set_level(10);
   set_hit_skill("combat/blunt/medium");
   set_skill("combat/blunt/medium", BASE_OFFENSE * 1);
   set_skill("combat/defense", BASE_DEFENSE * 6);

   equip_monster(({ DIR + "/obj/weapons/broom.c" }));
}
