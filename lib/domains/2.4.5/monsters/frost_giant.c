#include "../domain.h"

inherit "/std/monster";

void setup() {
   object obj;

   set_name("giant");
   set_gender( "male" );
   add_adj("frost");
   set_short("A frost giant");
   set_long("A frozen mass of muscle.  You really do not want to mess " +
      "with this giant.");
   set_race("giant");
   set_level(15);
   set_aggressive(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/frost_sword");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}

