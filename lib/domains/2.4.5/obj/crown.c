#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("crown");
   set_adj("small", "iron");
   set_short("A small iron crown");
   set_long("It looks cute.");
   set_gettable(1);
   set_slot("head");
   set_wear_message("$N $vput on $o.");
   set_remove_message("$N $vtake off $o");
   set_ac(1);
   set_size(1);
   set_value(30);
   set_weight(2);
}
