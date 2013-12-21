#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

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

   set_spell_chance(50);
   set_spell_damage(30);
   set_spell_message("Leo casts a blazing fireball at $t.\n");

/*
   EVENT_D->subscribe_event("do_give");
*/
}

/* 
   XXX finish Quest for Orc slayer?
   XXX Give user a castle if they ask for one....
*/

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
      respond("smile");
      count = 0;
   }
}

int do_give(object what, object who) {
   if (what->base_name() != DIR + "obj/gold_staff") {
      return 0;
   }
   if (who->is_completed_quest("Orc Slayer")) {
      return 0;
   } else {
      who->add_completed_quest("Orc Slayer");
      who->increase_expr(200);
      who->message("Congratulations!!! You have just completed the " +
         "Orc Slayer quest.\n");
      return 1;
   }
}
