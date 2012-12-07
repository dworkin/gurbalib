inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#include "../domain.h"

void setup() {
   object obj;

   set_name("giant");
   set_gender( "male" );
   add_adj("fire");
   set_in_room_desc("A fire giant");
   set_long("A mighty hot big guy.");
   set_race("giant");
   set_level(15);
   set_aggressive(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/fire_sword");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}

