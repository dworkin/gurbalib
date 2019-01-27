#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("eagle");
   set_short("An eagle");
   set_long("The eagle glares at you. It doesn't want to be disturbed.");

   set_race("animal");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_hit_string("claw");
}
