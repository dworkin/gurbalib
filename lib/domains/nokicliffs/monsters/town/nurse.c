#include "../../domain.h"

inherit NOKICLIFFS_VENDOR;

private int reload_first_aid_kit(object player) {
   object *pinv;
   int     fak_handled, i, dim;
   int     need, cost;

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
   set_long("The Noki Town nurse. You can always buy " +
      "first aid kits from her, even if they seem to be " +
      "out of stock.");
   set_race("human");
   set_level(1);
   add_item(DIR + "/obj/fak.c", 2);   
}
