#include "../domain.h"

inherit MONSTER;
inherit M_TRIGGERS;

#define INTERVAL 8
int count;


void setup() {
   set_name("leo");
   set_gender( "male" );
   set_short("Leo the Archwizard");
   set_long("Leo the Archwizard.");
   set_race("human");
   set_level(40);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 90);
   set_skill("combat/defense", 200);
}

/* XXX Need to do fireball spell as an attack option.
   XXX Quest for Orc slayer?
   XXX Give user a castle if they ask for one....
*/

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
      respond("smile");
      count = 0;
   }
}
