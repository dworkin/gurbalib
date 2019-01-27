#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

string *a_str;

void do_extra_actions() {
   if (is_fighting() && random(100) < 50) {
      respond(random_element(a_str));
   }
}

void setup(void) {
   set_name("thief");
   set_race("human");
   set_adj("suspicious looking");
   set_short("A suspicious looking thief");
   set_long("The thief seems to be doing something with the doors.");

   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   a_str = ({
      "say Noo! I got here first!",
      "say Get lost! This is my treasure!",
      "say It's mine it's mine it's mine!"
   });

   equip_monster(({
      DIR + "/obj/weapons/stiletto.c"
   }));
#ifdef USE_NOKICLIFFS
   equip_monster(({
      NOKICLIFFS_HOODED_CLOAK
   }));
#endif
}
