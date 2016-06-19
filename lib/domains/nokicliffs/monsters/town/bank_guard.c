#include "../../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("guard");
   add_id("bank guard");
   set_gender("male");
   set_short("The bank guard");
   set_long("The bank guard means business. " + 
      "You can tell this by his perfectly pressed " +
      "and heavily starched uniform and perfectly " +
      "shined shoes. He is here to keep your money "+
      "safe.");
   set_race("human");
   set_level(80);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 90);
   set_skill("combat/defense", 200);
   equip_monster(({ NOKICLIFFS_WEAPONS_DIR + "/baton.c" }));
}

