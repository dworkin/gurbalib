#include "../../domain.h"

inherit NOKICLIFFS_VENDOR;

private int reload_first_aid_kit(object player) {
   object *pinv;
   int fak_handled, i, dim, need, cost;

   pinv = player->query_inventory();
   dim = sizeof(pinv);
   for (i = 0; i < dim; i++) {
      if (pinv[i]->is_id("first aid kit")) {
         need = pinv[i]->query_max_charges() - pinv[i]->query_charges();
         cost = 5 * need;
         if (cost > player->query_total_money()) {
            player->message("You don't have enough coins " +
               "to reload your first aid kit.");
            return 1;
         }
         if (need == 0) {
            player->message("Your first aid kit is full.");
            return 1;
         }
         emit_successful_sale_msg(pinv[i], player);
         deduct_coins_from_buyer(cost, player);
         pinv[i]->reload(need);
         player->message("Your first aid kit has been reloaded " +
            "at the low, low cost of " + cost + " ducats.");
         return 1;
      }
   }

   return 0;
}

void handle_sale(string idx, object obj, object player) {
   int fak_handled;
   fak_handled = 0;
   if (obj->query_id() == "first aid kit") {
      fak_handled = reload_first_aid_kit(player);
   }
   if (!fak_handled) {
      ::handle_sale(idx, obj, player);
   }
}

void setup(void) {
   set_name("nurse");
   set_short("A nurse");
   set_long("The Noki Town nurse. You can buy various " +
      "items created from the very best practitioners of " +
      "the medical arts.");
   set_race("human");
   set_gender("female");
   set_level(1);
   set_will_buy(0);
   add_item(DIR + "/obj/endurance_potion", 10);
   add_item(DIR + "/obj/fak.c", 20);
   add_item(DIR + "/obj/mana_potion.c", 10);
}
