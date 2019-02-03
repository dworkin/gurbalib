#include "../../domain.h"

inherit "/std/shield";

void setup(void) {
   add_ids("tower shield");
   set_adj("large");
   set_short("A large tower shield");
   set_long("A large tower shield It has an intricate holy symbol " +
      "elaborately created on the front of it; perhaps the holy symbol " +
      "will help those who fight the unholy. It is heavy and sturdy.");

   set_wield_message("$N $vtake up $p $o.");
   set_unwield_message("$N $vremove $p $o.");
   set_wield_type("single");
   set_value(250);
   set_weight(5);
   set_ac(2);

   add_bane("holy");
}
