#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

void setup() {
   object obj, obj2;

   set_name("octopus");
   add_adj("giant");
   set_short("An octopus");
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

string query_miss_message() {
   if (random(1)) {
      return "The octopus says: Mumble.";
   } else {
      return "The octopus says: I will convert you to a pulp!";
   }
}
