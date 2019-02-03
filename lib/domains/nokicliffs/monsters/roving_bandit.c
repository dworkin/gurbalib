#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";
inherit DIR + "/lib/simple_block";

#define INTERVAL 5
int count;

private void equip(void) {
   equip_monster(({
      TWOFOURFIVE_DIR + "/obj/axe.c",
      TWOFOURFIVE_DIR + "/obj/jacket.c",
      TWOFOURFIVE_DIR + "/obj/rope.c",
      DIR + "/obj/climbing_gear.c"
   }));
}

void setup(void) {
   set_name("bandit");
   set_gender("male");
   add_adj("roving");
   set_short("A roving bandit");
   set_long("A roving bandit. He's certainly not here to help you " +
      "voluntarily.");
   set_race("human");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_hit_skill("combat/sharp/small");
   set_skill("combat/sharp/small", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 5);
   equip();
   add_coins("ducat", 100 + random(100));
}

void do_extra_actions(void) {
   count = count + 1;
   if (count >= INTERVAL) {
      switch(random(3)) {
      case 0:
         respond("say I know all there is to know and I ain't tellin'.");
         break;
      case 1:
         respond("say You ain't gonna survive much longer.");
         break;
      case 2:
         respond("say Nature doesn't care if ya live or die.");
         break;
      }
      count = 0;
   }
}

void monster_died(void) {
   if (!nilp(killer)) {
      killer->message("The bandit's dying words were: " +
         "Suzi saves sea shells from the seashore. " +
         "Try saying that ten times fa...");
   }
}
