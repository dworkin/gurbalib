#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

string *a_str;

void do_extra_actions(void) {
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

   set_level(15);
   set_hit_skill("combat/edge/small");
   set_skill("combat/edge/small", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);

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
