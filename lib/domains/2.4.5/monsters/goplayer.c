#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 8
int count;

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

void do_extra_actions() {
   if (this_environment()->query_current_problem() < 3) {
      count = count + 1;
      if (count > INTERVAL) {
         switch(random(5)) {
            case 0:
               respond("say Hm. This is tricky!");
               break;
            case 1:
               respond("say The moron who wrote this book didn't deal with " +
                  "this problem.");
               break;
            case 2:
               respond("say A throw in here should just be wasted.");
               break;
            case 3:
               respond("say This group is more alive than I am.");
               break;
            default:
               respond("say This is simple using oi-otoshi.");
               break;
         }
         count = 0;
      }
   }
}
