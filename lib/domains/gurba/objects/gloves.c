#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("gloves");
   set_adj("red");
   set_short("A pair of gloves");
   set_long("A pair of leather gloves.");
   set_gettable(1);
   set_slot("hands");
   set_wear_message("$N $vwear $o.");
   set_remove_message("$N $vremove $o.");
   set_value(20);
   set_size(4);
   set_weight(5);
}
