#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("oak");
   set_adj("big");
   set_short("A big oak");
   set_long("The oak is watching you with small gleaming eyes "+
            "and waves it's branches menacingly.");
   set_gender("neuter");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({ DIR + "/obj/weapons/oak_branch.c" }));
}
