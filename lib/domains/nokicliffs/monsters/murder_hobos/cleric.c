#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

void heal_comrade(object murder_hobo) {
   if (!murder_hobo->is_murder_hobo()) {
      return;
   }

   if (query_mana() < 5) {
      respond("say Not enough mana!");
      return;
   }

   respond("cast cure " + murder_hobo->query_name());
   this_object()->targeted_action("$N $vcast cure on " +
      murder_hobo->query_name() + ".", this_object());
}

void setup(void) {
   set_race("human");
   set_name("cleric");
   set_short("A cleric");
   set_long("The cleric is the party's healer and is "+
      "reasonably good in a fight.");

   set_skill("spell/cure", 200);
   set_max_mana(query_max_mana() * (random(3) + 1));
   set_mana(query_max_mana());

   equip_murder_hobo(({
      NOKICLIFFS_ARMORS_DIR + "/scale_mail.c",
      NOKICLIFFS_WEAPONS_DIR + "/mace.c"
   }));
}
