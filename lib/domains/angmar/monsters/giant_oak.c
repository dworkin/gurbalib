#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("oak");
   set_adj("giant");
   set_short("A giant oak");
   set_long("The oak is following your movements with its eyes. "+
            "Maybe you should leave while you can.");
   set_gender("neuter");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({ DIR + "/obj/weapons/oak_branch.c" }));
}
