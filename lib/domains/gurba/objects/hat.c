#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("sombrero", "hat");
   set_adj("large", "huge");
   set_short("A huge sombrero");
   set_long("Your average sombrero.");
   set_gettable(1);
   set_slot("head");
   set_wear_message("$N $vput $o on $p head.");
   set_remove_message("$N $vtake off $o.");
   set_value(20);
   set_weight(3);
   set_size(2);
}
