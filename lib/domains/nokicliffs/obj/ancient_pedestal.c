#include "../domain.h"

inherit "/std/object";

int cmd_put_relic_in_orb(string str) {
   string what, msg;
   object *inv;
   object potion;
   int i, dim;

   if (empty_str(str)) {
      return 0;
   }

   sscanf(str, "%s in orb", what);
   inv = this_player()->query_inventory();
   dim = sizeof(inv);
   for (i = 0; i < dim; i++) {
      if (inv[i]->is_id(what) &&
            inv[i]->property(ANCIENT_RELIC_PROP) == 1) {
         potion = clone_object(NOKICLIFFS_REJUV_POTION);
         potion->setup();
         msg = "$N $vput an ancient relic into the " +
            "orb. The orb's activity increases dramatically " +
            "for a moment as it accepts the offering. " +
            "A moment before the orb settles and returns " +
            "to normal a rejuvination potion pops out and " +
            "settles gently on the pedestal.";
         this_player()->targeted_action(msg, this_player());
         inv[i]->destruct();
         potion->move(query_environment());
         return 1;
      }
   }

   this_player()->message_orig(
      "That is not an appropriate offering to the Ancient One.\n");

   return 1;
}

void setup(void) {
   set_gettable(0);
   set_id("pedestal");
   add_adj("ancient");
   set_short("An ancient pedestal of the Ancient One");
   set_long("The ancient pedestal has a swirling orb " +
      "of mystical blue energy hoving just over the " +
      "top of it. The orb is actually a rift in the " +
      "spacetime continuum, a direct link to the " +
      "mysterious realms of the Ancient One. The "+
      "faeries have come here for thousand and " +
      "thousands of years to pay tribute to the " +
      "Ancient One. You can do the same by " +
      "putting any relic of the Ancient One's " +
      "avatars that you find (relics like finger " +
      "bones, locks of hair, and so on) in the orb.");

   add_action("cmd_put_relic_in_orb", "put");
}
