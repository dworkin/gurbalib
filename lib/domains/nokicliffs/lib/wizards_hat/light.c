#include "../../../../domain.h"

int lit;

int query_lit(void) {
   if (nilp(lit)) {
      lit = 0;
   }
   return lit;
}

private void light(void) {
   lit = 1;
}

private void extinguish(void) {
   lit = 0;
}

nomask int unlight_cmd(string str) {
   if (empty_str(str) || lowercase(str) != "lux") {
      write("Syntax: finito lux");
      return 1;
   }

   if (!query_lit()) {
      write("Your wizard's hat isn't glowing brightly anyway.");
      return 1;
   }

   TELL_ROOM(this_player(), this_player()->query_Name() + " says: finito lux!");
   extinguish();
   write("*poof*");
   TELL_ROOM(this_player(), this_player()->query_Name() + "'s wizard's " +
      " hat stops glowing brightly and goes dark.");
   return 1;
}

nomask int light_cmd(string str) {
   int enough_mana;
   if (empty_str(str)) {
      if (query_lit()) {
         write("Your wizard's hat is already shining brightly.");
         return 1;
      }
      TELL_ROOM(this_player(), this_player()->query_Name() + " says: lux!");
      enough_mana = this_player()->query_mana() > WIZHAT_COST;
      if (!enough_mana) {
         write("Your wizard's hat fizzles as you don't have enough mana " +
            "for that action.");
         return 1;
      }
      this_player()->set_mana(this_player()->query_mana() - WIZHAT_COST);
      light();
      write("*poof*");
      TELL_ROOM(this_player(), this_player()->query_Name() + "'s wizard's " +
         "hat starts to shine brightly.");
      return 1;
   }

   write("Syntax: lux");
   return 1;
}
