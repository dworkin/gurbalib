#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("player");
   set_gender( "male" );
   set_short("Go player");
   set_long("A man sitting beside a go board, concentrating on a problem.\n" +
      "He looks as if he wants help.  Why not look at his problem,\n" +
      "and tell him where to play?\n");

   set_race("human");
   set_level(10);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 100);
   set_skill("combat/defense", 100);
   set_aggressive(0);
}
