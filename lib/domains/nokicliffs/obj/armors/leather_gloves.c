#include "../../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("gloves");
   set_adj("leather");
   set_short("A pair of leather gloves");
   set_long("A standard pair of adventurer's leather gloves.");

   set_slot("hands");
   set_value(20);
   set_weight(1);
   set_ac(1);
}

void after_wear(object player) {
   if (!player) {
      return;
   }

   player->message("Slipping on the gloves makes you " +
      "feel like you are ready for some adventure.");
}
