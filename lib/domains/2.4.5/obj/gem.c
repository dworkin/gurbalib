#include "../domain.h"

inherit "/std/object";

void setup(void) {
   int temp;

   temp = random(4);

   if (temp == 0) {
      set_id("diamond");
      set_short("A diamond");
      set_long("A large cut diamond, it looks valuable.");
      set_value(random(125) + 830);
   } else if (temp == 1) {
      set_id("emerald");
      set_short("An emerald");
      set_long("A large cut emerald, it looks valuable.");
      set_value(random(125) + 230);
   } else if (temp == 2) {
      set_id("sapphire");
      set_short("A sapphire");
      set_long("A large cut sapphire, it looks valuable.");
      set_value(random(125) + 130);
   } else if (temp == 3) {
      set_id("ruby");
      set_short("A ruby");
      set_long("A large cut ruby, it looks valuable.");
      set_value(random(125) + 430);
   }
   add_ids("gem", "jewel");
   set_gettable(1);
   set_weight(1);
}
