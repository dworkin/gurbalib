#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("oak");
   set_adj("big");
   set_short("A big oak");
   set_long("The oak is watching you with small gleaming eyes "+
            "and waves it's branches menacingly.");
   set_gender("neuter");
   set_level(20);
   set_hit_skill("combat/blunt/large");
   set_skill("combat/blunt/large", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE * 2);

   equip_monster(({ DIR + "/obj/weapons/oak_branch.c" }));
}
