#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

string *attack_messages;

void do_extra_actions(void) {
   if (is_fighting()) {
      if (random(100) < 40) {
         respond(random_element(attack_messages));
         return;
      }
   }
}


void outside_message(string str) {
   object candy, fishing_rod, giver;
   string who;

   if (is_fighting()) {
      return;
   }

   str = ANSI_D->strip_colors(str);

   if (sscanf(str, "%s gives the candy to you.", who) == 1) {
      if (this_object()->present("candy")) {
         fishing_rod = this_object()->present("fishing rod");
         if (fishing_rod) {
            respond("grin");
            respond("drop fishing rod");
            respond("emote leaves the area.");
            this_object()->destruct();
         } else {
            respond("eat candy");
         }
      }
   }
}

void setup(void) {
   set_name("elf boy");
   set_adj("fishing");
   add_ids("elfboy", "fishing elf boy", "fishing elfboy", "fishing elf");
   set_short("A fishing elf boy");
   set_long("The fishing elf boy doesn't pay attention to you. " +
      "He's more interested in fishing.");
   set_gender("male");
   set_race("elf");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);
   set_objects(DIR + "/obj/fishing_rod.c");
   attack_messages = allocate(3);
   attack_messages[0] = "say Noo! Please, don't kill me!";
   attack_messages[1] = "say Mummy! mummy! Help! Help!";
   attack_messages[2] = "say Waaaaahhh!";
}
