#include "../domain.h"

inherit "/std/shield";

void setup(void) {
   set_id("shield");
   set_adj("round");
   set_short("A round shield");
   set_long("A round shield.");
   set_gettable(1);

   set_ac(2);

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o.");
   set_unwield_message("$N $vremove $p $o.");
   set_value(1);
   set_size(6);
   set_weight(10);
}
