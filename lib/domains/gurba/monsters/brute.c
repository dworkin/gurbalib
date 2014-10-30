#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("brute");

   set_gender("male");
   add_adj("huge");
   set_short("A huge brute");
   set_long("The brute looks huge.");
   set_level(15);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 250);
   set_skill("combat/defense", 200);
}
