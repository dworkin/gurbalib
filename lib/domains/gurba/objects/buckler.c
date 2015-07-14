#include "../domain.h"

inherit "/std/shield";

void setup(void) {
   set_id("buckler");
   set_adj("small", "round");
   set_short("A buckler");
   set_long("A small wooden buckler.");
   set_gettable(1);

   set_ac(1);

   set_wield_type("single");
   set_wield_message("$N $vequip $p $o.");
   set_unwield_message("$N $vremove $p $o.");
   set_value(20);
   set_size(1);
   set_weight(5);
}
