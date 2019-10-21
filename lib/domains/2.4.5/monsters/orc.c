#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";
inherit "/std/modules/m_block_exits";

#define INTERVAL 5
int count;

void setup() {
   object obj;
   set_name("orc");
   set_gender( "male" );
   add_adj("dirty");
   set_short("An orc");
   set_long("A dirty smelly orc.");
   set_race("orc");
   set_aggressive(1);
   set_level(random(2) + 1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   add_block("north");

   switch(random(3)) {
      case 0:
         obj = clone_object(DIR + "/obj/knife.c");
      case 1:
         obj = clone_object(DIR + "/obj/curved_knife.c");
      default:
         obj = clone_object(DIR + "/obj/axe.c");
   }
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
      switch(random(8)) {
         case 0:
            respond("say Kill him!");
            break;
         case 1:
            respond("say Bloody humans!");
            break;
         case 2:
            respond("say Stop him!");
            break;
         case 3:
            respond("say Get them!");
            break;
         case 4:
            respond("say Lets rip out some guts!");
            break;
         case 5:
            respond("say Kill 'em before they run away!");
            break;
         case 6:
            respond("say Put their heads on a pike!");
            break;
         default:
            respond("say What is that doing here?");
            break;
      }
      count = 0;
   }
}

int do_block(object who) {
   return 1;
}
