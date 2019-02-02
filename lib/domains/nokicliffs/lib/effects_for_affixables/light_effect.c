#include "../../../../domain.h"

private int is_lit;

int query_lit(void) {
   return is_lit;
}

void set_lit(int is_lit) {
   ::is_lit = is_lit;
}

void toggle_lit(void) {
   is_lit = !is_lit;
}

int affix_light_effect(string id, string on, object player) {
   string str;

   str = "$N $vtouch the " + on + " on $p " + id + " and it " +
      (is_lit ? "stops" : "starts") + " lighting the area.";
   player->simple_action(str, player);
   toggle_lit();
   return 1;
}
