#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   object obj;

   set_name("slim");
   set_gender( "male" );
   add_adj("large");
   set_short("Slim shady");
   set_long("This guy is skinny, he is also kind of creepy looking.  He " +
      "reminds you of an anemic scarecrow.");

   set_race("human");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_aggressive(0);

   obj = clone_object(DIR + "/obj/10ghat.c");
   obj->setup();
   obj->move(this_object());
   do_wear(obj);
}
