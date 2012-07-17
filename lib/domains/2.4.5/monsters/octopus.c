#include "../domain.h"
inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   object obj, obj2;

   set_name("octopus");
   add_adj("giant");
   set_in_room_desc("An octopus");
   set_long("A very big octopus with long arms, reaching for you.");

   set_level(10);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/chest.c");
   obj->move(this_object());
   obj->setup();

   obj2 = clone_object("/domains/required/objects/coin.c");
   obj2->set_amount(random(500) + 1);
   obj2->move(obj);
   obj2->setup();
}

// XXX Needs work still sea_bottom miss attack messages...

