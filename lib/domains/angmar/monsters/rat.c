#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("rat");
   set_short("A rat");
   set_long("A very ugly and smelly rat.");

   set_aggressive(1);
   set_race("animal");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);
   set_hit_string("nibble");
}
