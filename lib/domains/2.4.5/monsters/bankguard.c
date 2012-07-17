inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#include "../domain.h"

void setup() {
   object obj;

   set_name("guard");
   set_gender( "female" );
   set_in_room_desc("A guard");
   set_long("A big and sturdy guard.");
   set_race("human");
   set_level(11);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/bankkey.c");
   obj->setup();
   obj->move(this_object());
   obj = clone_object("/domains/required/objects/weapons/short_sword.c");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}
