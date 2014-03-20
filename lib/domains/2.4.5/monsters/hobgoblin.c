#include "../domain.h"

inherit "/std/monster";

void setup() {
   object obj;

   set_name("hobgoblin");
   set_gender( "male" );
   set_short("A hobgoblin");
   set_long("This hobgoblin looks really nasty..");
   set_race("hobgoblin");
   set_level(5);
   set_aggressive(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object("/domains/required/objects/coin.c");
   obj->set_amount(random(500) + 1);
   obj->move(obj);
   obj->setup();
}

