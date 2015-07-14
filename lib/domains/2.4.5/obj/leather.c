#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("armour");
   set_adj("leather");
   set_short("Leather armour");
   set_long("It looks supple.");
   set_gettable(1);
   set_slot("body");
   set_wear_message("$N $vput on $o.");
   set_remove_message("$N $vtake off $o.");
   set_ac(3);
   set_value(110);
   set_size(3);
   set_weight(10);
}
