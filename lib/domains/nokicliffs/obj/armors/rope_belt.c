#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("belt", "rope belt");
   add_adj("simple");
   set_short("A simple rope belt");
   set_long("This is a simple rope belt. It can be used only as a belt.");

   set_wear_message("$N $vtie $o.");
   set_remove_message("$N $vuntie $o.");

   set_slot("waist");
   set_ac(0);
   set_value(1);
   set_weight(1);
}
