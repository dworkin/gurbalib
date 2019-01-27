#include "../domain.h"

inherit "/std/container";
inherit MONEY_MAKER;

#define XP_FACTOR 10

private void targeted_action(string str) {
   this_player()->targeted_action(str, this_object());
}

int do_meditate(string str) {
   targeted_action("$N $vmeditate on life, the universe, and everything.");
   return 1;
}

int do_donate(string str) {
   int amt, worth, xp_gain;
   string type;
   object coins;

   if (empty_str(str)) {
      targeted_action("$N $vconsider donating coins to the chapel.");
   } else if (str == "coins") {
      write("How many coins?");
   } else if (sscanf(str, "%d %s", amt, type) == 2 && MONEY_D->is_currency(type)) {
      worth = MONEY_D->query_value(type);
      if (worth > 0) {
         worth *= amt;
         if (this_player()->query_total_money() >= worth) {
            if (!sizeof(query_inventory())) {
               make_money("ducat", 2)->move(this_object());
            }
            this_player()->add_money(type, -worth);
            xp_gain = worth / XP_FACTOR;
            targeted_action("$N $vdonate coins to the chapel. " +
               (xp_gain ? "It's a rewarding experience." : "It's a token gesture."));
            this_player()->increase_expr(xp_gain);
         } else {
            write("Donating more than you have is a nice gesture.");
         }
      }
   } else {
      targeted_action("$N $vtry to donate something worthless.");
   }

   return 1;
}

void setup(void) {
   set_id("box");
   set_adj("donation");
   set_short("A donation box");
   set_long("A donation box. You can donate coins to " +
      "show your appreciation and help to keep the place " +
      "beautiful.");

   add_action("do_donate", "donate");
   add_action("do_meditate", "meditate");
}
