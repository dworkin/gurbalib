#include "../../domain.h"

inherit "/std/shield";

void setup(void) {
   add_ids("round shield");
   set_adj("round");
   set_short("A round shield");
   set_long("This round shield is standard adventuring gear. It " +
      "is in excellent condition although there is nothing " +
      "exceptional about it.");

   set_wield_message("$N $vtake up $p $o.");
   set_unwield_message("$N $vremove $p $o.");
   set_wield_type("single");
   set_value(50);
   set_weight(2);
   set_ac(1);
}
