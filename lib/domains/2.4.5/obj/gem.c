inherit "/std/object";

#include "../domain.h"

void setup(void) {
   int temp;

   temp = random(3);
   if (temp == 0) {
      set_id("diamond");
      add_ids("gem","jewel");
      set_short("A diamond");
      set_long("A large cut diamond, it looks valuable.");
   } else if (temp == 1) {
      set_id("emerald");
      add_ids("gem","jewel");
      set_short("An emerald");
      set_long("A large cut emerald, it looks valuable.");
   } else if (temp == 2) {
      set_id("sapphire");
      add_ids("gem","jewel");
      set_short("A sapphire");
      set_long("A large cut sapphire, it looks valuable.");
   }
   set_gettable(1);
   set_value(random(250) + 300);
   set_weight(1);
}
