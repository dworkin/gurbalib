#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   object obj;

   set_name("kobold");
   set_gender( "male" );
   add_adj("filthy");
   set_short("A filthy little kobold");
   set_long("This dirty little creature is not your friend.  In fact he " +
      "looks rather grumpy.");
   set_race("kobold");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_aggressive(1);

   obj = clone_object(DIR + "/obj/minehelm.c");
   obj->setup();
   obj->move(this_object());
   do_wear(obj);
}
