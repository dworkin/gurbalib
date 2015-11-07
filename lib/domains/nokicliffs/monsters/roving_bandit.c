#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 5
int count;

private void equip() {
   object axe;
   object jacket;
   object climbing_gear;

   if (!this_object()->present("axe")) {
      axe = clone_object("/domains/2.4.5/obj/axe.c");
      axe->setup();
      axe->move(this_object());
      do_wield(axe);
   }

   if (!this_object()->present("jacket")) {
      jacket = clone_object("/domains/2.4.5/obj/jacket.c");
      jacket->setup();
      jacket->move(this_object());
      do_wear(jacket);
   }

   if (!this_object()->present("climbing gear")) {
      climbing_gear = clone_object(DIR + "/obj/climbing_gear.c");
      climbing_gear->setup();
      climbing_gear->move(this_object());
   }
}

void setup() {
   object obj;
   set_name("bandit");
   set_gender("male");
   add_adj("roving");
   set_short("A roving bandit");
   set_long("A roving bandit. He's certainly not here to help you " +
    "voluntarily.");
   set_race("human");
   set_aggressive(0);
   set_level(random(2) + 1);
   set_hit_skill("combat/sharp/small");
   set_skill("combat/unarmed", 50);
   set_skill("combat/sharp/small", 75);
   set_skill("combat/defense", 100);
   equip();
   add_coins("ducat", 100 + random(100));
}

void do_extra_actions() {
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

int do_block(object who) {
   return 1;
}
