#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("rat");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("filthy");
   set_short("A small filthy rat");
   set_long("The rat smells awful.");
   set_race("rodent");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}
