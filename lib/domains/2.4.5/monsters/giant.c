#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("giant");
   set_short("A giant");
   set_long("A massive giant.");

   set_aggressive(1);
   set_race("giant");
   set_level(15);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

