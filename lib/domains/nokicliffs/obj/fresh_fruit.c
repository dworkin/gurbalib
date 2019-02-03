#include "../domain.h"

inherit NOKICLIFFS_ROOT;
inherit DIR + "/lib/healing";

int calculate_amount(object player) {
   int amt;
   amt = 1 + random(10) + player->query_stat("con");
   if (amt < 10) {
      amt = 10;
   }
   return amt;
}

int do_eat(void) {
   if (!is_spoiled()) {
      set_doctor(this_object());
      set_patient(this_player());
      recover_end(calculate_amount(this_player()),
         "$N $venjoy some fresh fruit and $vfeel a boost of energy.");
   } else {
      this_player()->targeted_action("$N $vscrew up $P face as " +
         "$n eats some rotten fruit.", this_object());
   }
   this_object()->destruct();
   return 1;
}

string get_warn_short(void) {
   return "Less than fresh fruit";
}

string get_warn_long(void) {
   return "The fruit is looks less and less fresh.";
}

string get_spoiled_short(void) {
   return "Spoiled fruit";
}

string get_spoiled_long(void) {
   return "The fruit is spoiled. It probably tastes disgusting.";
}

string get_warn_message(void) {
   return "The fruit is browning. Better eat it soon to " +
      "get that energy boost.";
}

string get_spoil_message(void) {
   return "The fruit has been out for too long as has spoiled.";
}

void setup(void) {
   ::setup();
   set_id("fruit");
   set_short("Some fresh fruit, for a quick energy boost");
   set_long("The fruit is fresh and it " +
      "looks delicious. Better eat it before it spoils.");
   set_eatable(1);
   set_value(2);
   set_weight(1);
}
