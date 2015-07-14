#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("boots");
   set_adj("red");
   set_short("A pair of coolio boots");
   set_long("A pair of crocodile-skin boots.");
   set_gettable(1);
   set_slot("feet");
   set_wear_message("$N $vput on $o.");
   set_remove_message("$N $vtake off $o.");
   set_value(20);
   set_size(6);
   set_weight(6);
}
