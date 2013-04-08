#include "../domain.h"

inherit MONSTER;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

#define INTERVAL 5
int count;

void setup() {
   object obj;

   set_name("dragon");
   set_short("The cave dragon");
   set_long("A scaley mass of teeth and claws.");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 100);
   set_skill("combat/defense", 100);
   set_level(17);
   set_aggressive(1);

   obj = clone_object(DIR + "/obj/gem");
   obj->setup();
   obj->move(this_object());

   obj = clone_object("/domains/required/objects/coin.c");
   obj->set_amount(random(500) + 1);
   obj->move(this_object());
   obj->setup();
}

