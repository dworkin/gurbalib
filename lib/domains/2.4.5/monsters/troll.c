#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 5
int count;

void setup() {
   set_name("troll");
   add_adj("smelly");
   set_short("A large smelly troll");
   set_long("The troll looks like a messed up tree.");
   set_race("troll");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_level(8);
   set_aggressive(1);
}

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
      switch(random(2)) {
         case 0:
            respond("say Mumble...");
            break;
         case 1:
            respond("say Your mother was a %&#$(G%#!");
            break;
         default:
            respond("say what?");
            break;
      }
      count = 0;
   }
}
