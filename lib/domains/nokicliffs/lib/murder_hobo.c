#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

int is_murder_hobo(void) {
   return 1;
}

void attack(object who) {
   if (who && who->is_murder_hobo()) {
      return;
   }

   ::attack(who);
}

void do_extra_actions(void) {
   object cleric;

   if (query_name() == "bard") {
      return;
   }

   if (is_fighting() && query_hp() < 20) {
      if (query_name() == "cleric") {
         respond("cast cure");
         return;
      }

      cleric = query_environment()->present("cleric");
      if (cleric && cleric->is_murder_hobo()) {
         respond("say cleric!");
         cleric->heal_comrade(this_object());
      }
   }
}

void equip_murder_hobo(string *equip, varargs string coin, int x, int y) {
   equip += ({ TWOFOURFIVE_DIR + "/obj/gem.c" });
   equip_monster(equip);

   if (!coin) {
      coin = "royal";
      x = 5;
      y = 5;
   }

   add_coins(coin, x + random(y));
}

void create(void) {
   ::create();
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 3);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 6);
}