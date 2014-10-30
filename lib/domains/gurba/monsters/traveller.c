/* Demonstrates use of m_wander for testing purposes.  Cerihan 3/14/09 */
#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_wander";

void setup(void) {
   set_name("traveller");

   /* Leave out the gender specification, get a random one */
   /*  set_gender(0); */

   add_adj("wandering");
   set_short("A wandering traveller");
   set_long("This tired-looking person just happens to be passing through " +
      "the area..");
   set_race("human");
   set_level(random(8) + 5);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   set_wander_area("Gurba");
   start_wander(10, 20);
}
