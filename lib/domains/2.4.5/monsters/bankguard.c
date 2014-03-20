#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";
inherit "/std/modules/m_block_exits";

void setup() {
   object obj;

   set_name("guard");
   set_gender( "female" );
   set_short("A guard");
   set_long("A big and sturdy guard.");
   set_race("human");
   set_level(11);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/bankkey.c");
   obj->setup();
   obj->move(this_object());
   obj = clone_object("/domains/required/objects/short_sword.c");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}
