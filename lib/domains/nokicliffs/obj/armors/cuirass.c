#include "../../domain.h"

inherit DIR + "/lib/armor";

int magical_properties_active;
int bonus;

void setup(void) {
   set_id("cuirass");
   add_adj("metal", "magical");
   set_short("A magical cuirass");
   set_long("This metal cuirass has been forged in ancient fires. It " +
      "seems to have some magical properties imbued into it but the " +
      "precise nature of them are known only to the ancient forgers " +
      "and the immortals.");
   set_medium();
}

int query_magical_properties_active(void) {
   return magical_properties_active;
}

void after_wear(object player) {
   if (!player) {
      return;
   }

   magical_properties_active = 1;
   bonus = player->query_level() + random(10) + 1;
   player->message("You feel more skillful.");

   if (query_wizard(player)) {
      player->message("In fact you feel this much more: " + bonus);
   }

   player->set_skill_bonus(bonus);
}

void after_unwear(object player, string cmd) {
   ::after_unwear(player, cmd);

   magical_properties_active = 0;

   if (!player) {
      return;
   }

   if (!nilp(cmd)) {
      player->message("You feel less skillful.");
   }

   player->set_skill_bonus(player->query_skill_bonus() - bonus);
}
