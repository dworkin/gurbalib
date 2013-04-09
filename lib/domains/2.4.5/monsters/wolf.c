#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("wolf");
   set_race("wolf");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("scraggly");
   set_short("A wolf");
   set_long("The grey wolf, running around.  It has some big dangerous teeth.");
   set_level(6);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

