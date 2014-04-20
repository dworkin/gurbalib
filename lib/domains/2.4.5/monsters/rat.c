#include "../domain.h"

inherit "/std/monster";

int count;

void setup() {
   object obj;

   set_name("rat");
   add_adj("black");
   set_short("An ugly black rat");
   set_long("This sucker is huge.");
   set_race("rat");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_level(3);
   set_aggressive(1);

   obj = clone_object(DIR + "/obj/stone.c");
   obj->setup();
   obj->move(this_object());
}

