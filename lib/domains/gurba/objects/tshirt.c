#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("t-shirt", "tshirt");
   set_adj("gurbalib");
   set_short("A flashy T-shirt");
   set_long("It reads: I crashed GurbaLib and all I got was this " +
      "stupid T-Shirt!");
   set_gettable(1);
   set_slot("torso");
   set_wear_message("$N $vput on $o, and suddenly $vlook a lot better.");
   set_remove_message("$N $vtake off $o, and suddenly $vlook dull.");
   set_ac(1);
   set_value(20);
   set_size(1);
   set_weight(3);
}
