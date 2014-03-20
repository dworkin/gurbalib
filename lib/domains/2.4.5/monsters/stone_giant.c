#include "../domain.h"

inherit "/std/monster";

void setup() {
   object obj;

   set_name("giant");
   set_gender( "male" );
   add_adj("stone");
   set_short("A stone giant");
   set_long("A huge marble skinned hulking tower of a man.");
   set_race("giant");
   set_level(15);
   set_aggressive(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/stone_sword");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}

